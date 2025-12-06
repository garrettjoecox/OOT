#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Wood02/z_en_wood02.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> bonkedTrees;

static void InitTreesBehavior() {
    bonkedTrees.clear();

    COND_VB_SHOULD(VB_TREE_DROP_ITEM, IS_ROGUELIKE, {
        EnWood02* treeActor = va_arg(args, EnWood02*);
        int16_t actorIndex = GetActorListIndex((Actor*)treeActor);

        *should = false;

        if (actorIndex == -1) {
            actorIndex = treeActor->actor.home.pos.x + treeActor->actor.home.pos.z;
        }

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (bonkedTrees.find(tupleKey) == bonkedTrees.end()) {
            RogueLike::XP::SpawnXPGroup(treeActor->actor.world.pos, CVarGetInteger("gRogueLike.XPDrop.Trees", 20));
            bonkedTrees.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitTreesBehavior, { "IS_ROGUELIKE" });
