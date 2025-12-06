#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/custom-item/CustomItem.h"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> collectedItems;

static void InitFreestandingItemsBehavior() {
    collectedItems.clear();

    COND_ID_HOOK(ShouldActorInit, ACTOR_EN_ITEM00, IS_ROGUELIKE, [](void* actor, bool* should) {
        EnItem00* enItem00 = static_cast<EnItem00*>(actor);

        if (enItem00->actor.params == ITEM00_NONE) {
            return;
        }

        int xpAmount = 0;
        switch (enItem00->actor.params) {
            case ITEM00_RUPEE_GREEN:
                xpAmount = 1;
                break;
            case ITEM00_RUPEE_BLUE:
                xpAmount = 5;
                break;
            case ITEM00_RUPEE_RED:
                xpAmount = 20;
                break;
            case ITEM00_RUPEE_PURPLE:
                xpAmount = 50;
                break;
            case ITEM00_HEART:
                xpAmount = 20;
                break;
            case ITEM00_HEART_PIECE:
                xpAmount = 100;
                break;
            case ITEM00_HEART_CONTAINER:
                xpAmount = 200;
                break;
            default:
                xpAmount = 10;
                break;
        }

        int16_t actorIndex = GetActorListIndex((Actor*)enItem00);

        *should = false;

        if (actorIndex == -1) {
            actorIndex = enItem00->actor.home.pos.x + enItem00->actor.home.pos.z;
        }

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (collectedItems.find(tupleKey) == collectedItems.end()) {
            RogueLike::XP::SpawnXPOrb(enItem00->actor.world.pos, xpAmount,
                                      CustomItem::STOP_BOBBING | CustomItem::ENABLE_GRAVITY);
            collectedItems.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitFreestandingItemsBehavior, { "IS_ROGUELIKE" });
