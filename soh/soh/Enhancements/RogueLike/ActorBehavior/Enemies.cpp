#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

uint16_t enemyPlatingMax = 1;
std::vector<Actor*> platedEnemies;
uint16_t previousRoll = -1;

static void InitEnemyBehavior() {
    COND_HOOK(OnActorUpdate, IS_ROGUELIKE, [](void* actor) {
        Actor* refActor = static_cast<Actor*>(actor);
        if (refActor->category != ACTORCAT_ENEMY) {
            return;
        }

        if (refActor->colorFilterParams != 0) {
            refActor->colorFilterTimer = 1000;
        }
    });

    COND_HOOK(OnSceneSpawnActors, IS_ROGUELIKE, []() {
        ActorListEntry actorList = gPlayState->actorCtx.actorLists[ACTORCAT_ENEMY];

        for (int i = platedEnemies.size(); i < enemyPlatingMax; i++) {
            uint16_t enemyRoll = rand() % (actorList.length - 1);
            if (enemyRoll == previousRoll) {
                enemyRoll++;
            }

            Actor* currentActor = actorList.head;
            for (int j = 0; j < actorList.length; j++) {
                if (j == enemyRoll) {
                    Actor_SetColorFilter(currentActor, 0x8000, 150, 0, 1000);
                    platedEnemies.push_back(currentActor);
                    previousRoll = enemyRoll;
                    break;
                }
                currentActor = currentActor->next;
            }
        }
    });

    COND_HOOK(OnSceneInit, IS_ROGUELIKE, [](u16 sceneNum) { 
        platedEnemies.clear();
        previousRoll = -1;
    });
}

static RegisterShipInitFunc initFunc(InitEnemyBehavior, { "IS_ROGUELIKE" });
