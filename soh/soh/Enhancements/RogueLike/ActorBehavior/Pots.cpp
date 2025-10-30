#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_Obj_Tsubo/z_obj_tsubo.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> brokenPots;

static void InitPotsBehavior() {
    brokenPots.clear();

    COND_VB_SHOULD(VB_POT_DROP_ITEM, IS_ROGUELIKE, {
        ObjTsubo* potActor = va_arg(args, ObjTsubo*);
        int16_t actorIndex = GetActorListIndex((Actor*)potActor);

        *should = false;

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (brokenPots.find(tupleKey) == brokenPots.end()) {
            RogueLike::XP::SpawnXPGroup(potActor->actor.world.pos, CVarGetInteger("gRogueLike.XPDrop.Pots", 20));
            brokenPots.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitPotsBehavior, { "IS_ROGUELIKE" });
