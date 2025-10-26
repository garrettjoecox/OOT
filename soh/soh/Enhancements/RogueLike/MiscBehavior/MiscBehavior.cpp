#include "MiscBehavior.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"

extern "C" {
#include "variables.h"
}

// Entry point for the module, run once on game boot
void RogueLike::MiscBehavior::Init() {
}

void RogueLike::MiscBehavior::OnLoadGame() {
    gSaveContext.ship.quest.data.rogueLike.stats[RL_ATTACK] = 20;
    gSaveContext.ship.quest.data.rogueLike.stats[RL_DEFENSE] = 10;
}
