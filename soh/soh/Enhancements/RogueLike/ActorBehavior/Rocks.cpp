#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Ishi/z_en_ishi.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> brokenRocks;

static void InitRocksBehavior() {
    brokenRocks.clear();

    COND_VB_SHOULD(VB_ROCK_DROP_ITEM, IS_ROGUELIKE, {
        EnIshi* rockActor = va_arg(args, EnIshi*);
        int16_t actorIndex = GetActorListIndex((Actor*)rockActor);

        *should = false;

        if (actorIndex == -1) {
            actorIndex = rockActor->actor.home.pos.x + rockActor->actor.home.pos.z;
        }

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (brokenRocks.find(tupleKey) == brokenRocks.end()) {
            RogueLike::XP::SpawnXPGroup(rockActor->actor.world.pos, CVarGetInteger("gRogueLike.XPDrop.Rocks", 20));
            brokenRocks.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitRocksBehavior, { "IS_ROGUELIKE" });
