#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
}

// This is kind of a catch-all for things that are simple enough to not need their own file.
static void MiscVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, va_list optionalArg) {
    switch (id) {
        case VB_OPEN_KOKIRI_FOREST: {
            *should = true;
            break;
        }
        default:
            break;
    }
}

static void OnEnemyDefeatHandler(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    switch (actor->id) {
        default:
            RogueLike::XP::SpawnXPGroup(actor->world.pos, 50);
            break;
    }
}

static void InitActorBehavior() {
    COND_HOOK(OnEnemyDefeat, IS_ROGUELIKE, OnEnemyDefeatHandler);
    COND_HOOK(OnVanillaBehavior, IS_ROGUELIKE, MiscVanillaBehaviorHandler);
}

static RegisterShipInitFunc initFunc(InitActorBehavior, { "IS_ROGUELIKE" });