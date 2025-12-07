#include "RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/ShipInit.hpp"

std::vector<uint32_t> RogueLike::requiredRewards;

// Entry point for the module, run once on game boot
static void InitRogueLike() {
}

static RegisterShipInitFunc initFunc(InitRogueLike, {});
