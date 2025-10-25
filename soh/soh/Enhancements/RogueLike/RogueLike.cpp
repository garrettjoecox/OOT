#include "RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/RogueLike/ActorBehavior/ActorBehavior.h"
#include "soh/Enhancements/RogueLike/MiscBehavior/MiscBehavior.h"
#include "soh/Enhancements/RogueLike/GUI/GUI.h"

extern "C" {
#include <z64save.h>
#include "macros.h"
#include "variables.h"
#include "functions.h"

extern SaveContext gSaveContext;
}

// When a save is loaded, we want to unregister all hooks and re-register them
static void OnLoadGame(int32_t fileNum) {
    RogueLike::MiscBehavior::OnLoadGame();
    RogueLike::ActorBehavior::OnLoadGame();
    RogueLike::GUI::OnLoadGame();

    ShipInit::Init("IS_ROGUELIKE");
}

// Entry point for the module, run once on game boot
void RogueLike::Init() {
    RogueLike::MiscBehavior::Init();
    RogueLike::ActorBehavior::Init();
    RogueLike::GUI::Init();

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>(OnLoadGame);
}

static RegisterShipInitFunc initFunc(RogueLike::Init);
