#include "RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/RogueLike/ActorBehavior/ActorBehavior.h"
#include "soh/Enhancements/RogueLike/MiscBehavior/MiscBehavior.h"
#include "soh/Enhancements/RogueLike/GUI/GUI.h"
#include "soh/Enhancements/custom-item/CustomItem.h"

extern "C" {
#include <z64save.h>
#include "macros.h"
#include "variables.h"
#include "functions.h"

extern SaveContext gSaveContext;
extern PlayState* gPlayState;
}

// When a save is loaded, we want to unregister all hooks and re-register them
static void OnLoadGame(int32_t fileNum) {
    RogueLike::MiscBehavior::OnLoadGame();
    RogueLike::ActorBehavior::OnLoadGame();
    RogueLike::GUI::OnLoadGame();

    ShipInit::Init("IS_ROGUELIKE");
}

// Entry point for the module, run once on game boot
void RogueLike::Init() {
    RogueLike::MiscBehavior::Init();
    RogueLike::ActorBehavior::Init();
    RogueLike::GUI::Init();

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>(OnLoadGame);
}

void RogueLike::SpawnXPOrb(Vec3f spawnPos, int32_t amount) {
    CustomItem::Spawn(
        spawnPos.x, spawnPos.y + 10.0f, spawnPos.z, 0, CustomItem::STOP_BOBBING | CustomItem::TOSS_ON_SPAWN, amount,
        [](Actor* actor, PlayState* play) {
            gSaveContext.ship.quest.data.rogueLike.experiencePoints += CUSTOM_ITEM_PARAM;
            Sfx_PlaySfxCentered(NA_SE_SY_RUPY_COUNT);
        },
        [](Actor* actor, PlayState* play) {
            Matrix_Scale(15.0f, 15.0f, 15.0f, MTXMODE_APPLY);
            Matrix_Translate(0.0f, -40.0f, 0.0f, MTXMODE_APPLY);

            int32_t amount = CUSTOM_ITEM_PARAM;
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

void RogueLike::SpawnXPGroup(Vec3f spawnPos, int32_t amount) {
    int32_t remainingAmount = amount;

    while (remainingAmount > 0) {
        std::vector<int32_t> orbSizes = { 1 };

        if (remainingAmount >= 200)
            orbSizes.push_back(200);
        if (remainingAmount >= 50)
            orbSizes.push_back(50);
        if (remainingAmount >= 20)
            orbSizes.push_back(20);
        if (remainingAmount >= 5)
            orbSizes.push_back(5);

        int32_t orbAmount = orbSizes[Rand_ZeroOne() * orbSizes.size()];

        SpawnXPOrb(spawnPos, orbAmount);
        remainingAmount -= orbAmount;
    }
}

static RegisterShipInitFunc initFunc(RogueLike::Init);
