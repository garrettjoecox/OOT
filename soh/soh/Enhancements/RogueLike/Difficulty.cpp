#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorMaximumHealth.h"

extern "C" {
#include "variables.h"
#include "functions.h"
#include "macros.h"

extern PlayState* gPlayState;
}

#define BASE_DIFFICULTY CVarGetFloat("gRogueLike.BaseDifficulty", 5000.0f)
#define GROWTH_RATE CVarGetFloat("gRogueLike.DifficultyGrowthRate", 1.3f)

void RogueLike::Difficulty::IndicateActivity() {
    gSaveContext.ship.quest.data.rogueLike.lastActivity = GetUnixTimestamp();
}

float RogueLike::Difficulty::GetProgressToNextLevel() {
    u32 currentDifficulty = gSaveContext.ship.quest.data.rogueLike.difficulty;

    u32 currentLevel = GetCurrentLevel();
    u32 difficultyForCurrentLevel = ConvertLevelToDifficulty(currentLevel);
    u32 difficultyForNextLevel = ConvertLevelToDifficulty(currentLevel + 1);

    return static_cast<float>(currentDifficulty - difficultyForCurrentLevel) /
           static_cast<float>(difficultyForNextLevel - difficultyForCurrentLevel);
}

u32 RogueLike::Difficulty::GetCurrentLevel() {
    return RogueLike::Difficulty::ConvertDifficultyToLevel(gSaveContext.ship.quest.data.rogueLike.difficulty);
}

u32 RogueLike::Difficulty::ConvertDifficultyToLevel(u32 difficulty) {
    return static_cast<u32>(logf((difficulty * (GROWTH_RATE - 1) / BASE_DIFFICULTY) + 1) / logf(GROWTH_RATE));
}

u32 RogueLike::Difficulty::ConvertLevelToDifficulty(u32 level) {
    return static_cast<u32>(BASE_DIFFICULTY * ((powf(GROWTH_RATE, level) - 1) / (GROWTH_RATE - 1)));
}

void RogueLike::Difficulty::IncrementDifficulty(u32 amount) {
    u32 oldLevel = GetCurrentLevel();
    gSaveContext.ship.quest.data.rogueLike.difficulty += amount;
    u32 newLevel = GetCurrentLevel();

    if (newLevel != oldLevel) {
        // Loop over all actors and adjust health

        Actor* actor = gPlayState->actorCtx.actorLists[ACTORCAT_ENEMY].head;
        while (actor != NULL) {
            actor->colChkInfo.health = (actor->colChkInfo.health / (oldLevel + 1)) * (newLevel + 1);
            SetActorMaximumHealth(actor, (GetActorMaximumHealth(actor) / (oldLevel + 1)) * (newLevel + 1));
            actor = actor->next;
        }
    }
}

static void OnLoadGame() {
    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, []() {
        if (GetUnixTimestamp() - gSaveContext.ship.quest.data.rogueLike.lastActivity >= 10 * 1000) {
            RogueLike::Difficulty::IncrementDifficulty(1);
        }
    });

    COND_HOOK(OnActorInit, IS_ROGUELIKE, [](void* refActor) {
        Actor* actor = static_cast<Actor*>(refActor);

        if (actor->category != ACTORCAT_ENEMY) {
            return;
        }

        actor->colChkInfo.health *= (RogueLike::Difficulty::GetCurrentLevel() + 1);
    });

    COND_VB_SHOULD(VB_APPLY_DAMAGE_TO_ACTOR, IS_ROGUELIKE, {
        Actor* actor = va_arg(args, Actor*);
        u32 damageEffect = va_arg(args, u32);
        u32 damage = va_arg(args, u32);
        u32 dmgFlags = va_arg(args, u32);

        if (actor->category == ACTORCAT_PLAYER) {
            SPDLOG_INFO("Incoming Damage Before: {}", damage);

            // Player taking damage, 1 Point addition per Difficulty Level
            damage *= RogueLike::Difficulty::GetCurrentLevel() + 1;

            // Player taking damage, 1 Point reduction per Defense Level
            damage /= (gSaveContext.ship.quest.data.rogueLike.stats[RL_DEFENSE] + 1);

            SPDLOG_INFO("Incoming Damage After: {}", damage);
        } else if (actor->category == ACTORCAT_ENEMY) {
            SPDLOG_INFO("Outgoing Damage Before: {}", damage);

            if (dmgFlags & DMG_SLASH_KOKIRI) {
                // This was a Kokiri Sword attack, double damage bonus etc
                // damage = static_cast<u32>(damage * 2.0f);
            }

            // Enemy taking damage, 1 Point addition per Attack Level
            damage *= gSaveContext.ship.quest.data.rogueLike.stats[RL_ATTACK] + 1;

            SPDLOG_INFO("Outgoing Damage After: {}", damage);
        } else {
            return;
        }

        // Overwrite damage amount
        actor->colChkInfo.damage = damage;
    });
}

static RegisterShipInitFunc initFunc(OnLoadGame, { "IS_ROGUELIKE" });
