#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

#define ENEMY_PLATE_MAX CVarGetInteger("gRogueLike.EnemyPlateMax", 3)
#define PLATE_CHANCE CVarGetInteger("gRogueLike.EnemyPlateChance", 25)

uint16_t plateChanceRoll = -1;
std::vector<Actor*> platedEnemies;

static void InitEnemyBehavior() {
    COND_HOOK(OnActorInit, IS_ROGUELIKE, [](void* actor) {
        Actor* refActor = static_cast<Actor*>(actor);

        if (refActor->category != ACTORCAT_ENEMY) {
            return;
        }

        if (platedEnemies.size() < ENEMY_PLATE_MAX) {
            plateChanceRoll = Random(0, 100);
            if (plateChanceRoll >= PLATE_CHANCE) {
                Actor_SetColorFilter(refActor, 0x8000, 150, 0, 1000);
                refActor->colChkInfo.health *= 5;
                platedEnemies.push_back(refActor);
            }
        }
    });

    COND_HOOK(OnActorUpdate, IS_ROGUELIKE, [](void* actor) {
        Actor* refActor = static_cast<Actor*>(actor);
        if (refActor->id == ACTOR_OBJ_TSUBO && refActor->params == 256) {
            Actor_SetColorFilter(refActor, 0x1000, 150, 0, 1000);
            return;
        }

        if (refActor->category != ACTORCAT_ENEMY) {
            return;
        }

        for (auto& enemy : platedEnemies) {
            if (enemy == refActor) {
                Actor_SetColorFilter(refActor, 0x8000, 150, 0, 1000);
                break;
            }
        }
    });

    COND_HOOK(OnSceneInit, IS_ROGUELIKE, [](u16 sceneNum) { platedEnemies.clear(); });
}

static RegisterShipInitFunc initFunc(InitEnemyBehavior, { "IS_ROGUELIKE" });
