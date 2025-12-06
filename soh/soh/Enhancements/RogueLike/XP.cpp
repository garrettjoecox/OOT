#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/custom-item/CustomItem.h"

extern "C" {
#include "variables.h"
#include "functions.h"
#include "macros.h"

extern PlayState* gPlayState;
}

extern std::shared_ptr<RogueLike::GUI::LevelUpWindow> mLevelUpWindow;
extern std::map<RoguelikeStats, std::pair<std::string, std::string>> rogueLikeStatMap;

#define BASE_XP CVarGetFloat("gRogueLike.BaseXP", 100.0f)
#define GROWTH_RATE CVarGetFloat("gRogueLike.XPGrowthRate", 1.3f)

float RogueLike::XP::GetProgressToNextLevel() {
    u32 currentXP = gSaveContext.ship.quest.data.rogueLike.xp;

    u32 currentLevel = GetCurrentLevel();
    u32 xpForCurrentLevel = ConvertLevelToXP(currentLevel);
    u32 xpForNextLevel = ConvertLevelToXP(currentLevel + 1);

    return static_cast<float>(currentXP - xpForCurrentLevel) / static_cast<float>(xpForNextLevel - xpForCurrentLevel);
}

u32 RogueLike::XP::GetCurrentLevel() {
    return RogueLike::XP::ConvertXPToLevel(gSaveContext.ship.quest.data.rogueLike.xp);
}

u32 RogueLike::XP::ConvertXPToLevel(u32 xp) {
    return static_cast<u32>(logf((xp * (GROWTH_RATE - 1) / BASE_XP) + 1) / logf(GROWTH_RATE));
}

u32 RogueLike::XP::ConvertLevelToXP(u32 level) {
    return static_cast<u32>(BASE_XP * ((powf(GROWTH_RATE, level) - 1) / (GROWTH_RATE - 1)));
}

void RogueLike::XP::GrantXP(u32 amount) {

    u32 oldLevel = GetCurrentLevel();
    gSaveContext.ship.quest.data.rogueLike.xp += amount;
    RogueLike::Difficulty::IndicateActivity();
    u32 newLevel = GetCurrentLevel();

    if (newLevel != oldLevel) {
        Sfx_PlaySfxCentered(NA_SE_SY_CORRECT_CHIME);
        mLevelUpWindow->Show();
    }
}

void RogueLike::XP::SpawnXPOrb(Vec3f spawnPos, u32 amount, int16_t flags) {
    CustomItem::Spawn(
        spawnPos.x, spawnPos.y + 10.0f, spawnPos.z, 0, flags, amount,
        [](Actor* actor, PlayState* play) {
            RogueLike::XP::GrantXP(CUSTOM_ITEM_PARAM);
            Sfx_PlaySfxCentered(NA_SE_SY_RUPY_COUNT);
        },
        [](Actor* actor, PlayState* play) {
            Matrix_Scale(15.0f, 15.0f, 15.0f, MTXMODE_APPLY);
            Matrix_Translate(0.0f, -40.0f, 0.0f, MTXMODE_APPLY);

            u32 amount = CUSTOM_ITEM_PARAM;
            GetItemDrawID drawId = GID_RUPEE_GREEN;

            if (amount >= 200) {
                drawId = GID_RUPEE_GOLD;
            } else if (amount >= 50) {
                drawId = GID_RUPEE_PURPLE;
            } else if (amount >= 20) {
                drawId = GID_RUPEE_RED;
            } else if (amount >= 5) {
                drawId = GID_RUPEE_BLUE;
            }

            GetItem_Draw(play, drawId);

            // Slowly move towards the player
            Player* player = GET_PLAYER(play);

            // Don't magnet till it hits the ground
            if (actor->bgCheckFlags & 1 && !Player_InBlockingCsMode(gPlayState, player)) {
                if (actor->xzDistToPlayer < 100.0f) {
                    s16 targetYaw = Actor_WorldYawTowardActor(actor, &player->actor);
                    actor->world.rot.y = targetYaw;

                    // the further away, the slower it moves
                    const f32 desiredSpeed = ((actor->xzDistToPlayer - 10.0f) / 90.0f) * (0.01f - 3.0f) + 3.0f;
                    actor->speedXZ = desiredSpeed;
                }

                if (actor->xzDistToPlayer < 10.0f) {
                    CUSTOM_ITEM_FLAGS |= CustomItem::KILL_ON_TOUCH;
                }
            }
        });
}

void RogueLike::XP::SpawnXPGroup(Vec3f spawnPos, u32 amount) {
    u32 remainingAmount = amount;

    while (remainingAmount > 0) {
        std::vector<u32> orbSizes = { 1 };

        if (remainingAmount >= 200)
            orbSizes.push_back(200);
        if (remainingAmount >= 50)
            orbSizes.push_back(50);
        if (remainingAmount >= 20)
            orbSizes.push_back(20);
        if (remainingAmount >= 5)
            orbSizes.push_back(5);

        u32 orbAmount = orbSizes[Rand_ZeroOne() * orbSizes.size()];

        SpawnXPOrb(spawnPos, orbAmount);
        remainingAmount -= orbAmount;
    }
}

void RogueLike::XP::UpdatePlayerStats() {
    gSaveContext.healthCapacity = 0x30 + (gSaveContext.ship.quest.data.rogueLike.stats[RL_HEALTH] * 0x10);
}
