#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Kusa/z_en_kusa.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> brokenGrass;

static void InitGrassBehavior() {
    brokenGrass.clear();

    COND_VB_SHOULD(VB_GRASS_DROP_ITEM, IS_ROGUELIKE, {
        EnKusa* grassActor = va_arg(args, EnKusa*);
        int16_t actorIndex = GetActorListIndex((Actor*)grassActor);

        *should = false;

        if (actorIndex == -1) {
            actorIndex = grassActor->actor.home.pos.x + grassActor->actor.home.pos.z;
        }

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (brokenGrass.find(tupleKey) == brokenGrass.end()) {
            RogueLike::XP::SpawnXPGroup(grassActor->actor.world.pos, CVarGetInteger("gRogueLike.XPDrop.Grass", 20));
            brokenGrass.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitGrassBehavior, { "IS_ROGUELIKE" });
