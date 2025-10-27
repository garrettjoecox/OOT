#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"

extern "C" {
#include "variables.h"
}

// This is kind of a catch-all for things that are simple enough to not need their own file.
static void MiscVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, va_list optionalArg) {
    switch (id) {
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

// Entry point for the module, run once on game boot
void RogueLike::ActorBehavior::Init() {
}

void RogueLike::ActorBehavior::OnLoadGame() {
    RogueLike::ActorBehavior::InitEnBoxBehavior();
    RogueLike::ActorBehavior::InitEnDnsBehavior();
    RogueLike::ActorBehavior::InitEnIshiBehavior();
    RogueLike::ActorBehavior::InitEnKusaBehavior();
    RogueLike::ActorBehavior::InitEnWood02Behavior();
    RogueLike::ActorBehavior::InitObjTsuboBehavior();

    COND_HOOK(OnEnemyDefeat, IS_ROGUELIKE, OnEnemyDefeatHandler);
    COND_HOOK(OnVanillaBehavior, IS_ROGUELIKE, MiscVanillaBehaviorHandler);
}
