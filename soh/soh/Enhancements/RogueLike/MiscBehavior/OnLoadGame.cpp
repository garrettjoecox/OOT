#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "functions.h"
}

static void OnLoadGame(int32_t fileNum) {
    ShipInit::Init("IS_ROGUELIKE");

    if (IS_ROGUELIKE) {
        // TODO: These should all really be moved to OnFileCreate
        gSaveContext.ship.quest.data.rogueLike.stats[RL_ATTACK] = 0;
        gSaveContext.ship.quest.data.rogueLike.stats[RL_DEFENSE] = 0;
    
        Flags_SetEventChkInf(EVENTCHKINF_OPENED_THE_DOOR_OF_TIME);
        Flags_SetEventChkInf(EVENTCHKINF_SHOWED_MIDO_SWORD_SHIELD);
        Flags_SetEventChkInf(EVENTCHKINF_SPOKE_TO_MIDO_AFTER_DEKU_TREES_DEATH);
    }
}

static RegisterShipInitFunc initFunc([]() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>(OnLoadGame);
}, {});
