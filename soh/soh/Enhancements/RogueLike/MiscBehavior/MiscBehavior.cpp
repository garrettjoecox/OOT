#include "soh/Enhancements/RogueLike/RogueLike.h"

extern "C" {
#include "variables.h"
#include "functions.h"
}

// Entry point for the module, run once on game boot
void RogueLike::MiscBehavior::Init() {
}

void RogueLike::MiscBehavior::OnLoadGame() {
    gSaveContext.ship.quest.data.rogueLike.stats[RL_ATTACK] = 0;
    gSaveContext.ship.quest.data.rogueLike.stats[RL_DEFENSE] = 0;

    Flags_SetEventChkInf(EVENTCHKINF_OPENED_THE_DOOR_OF_TIME);
    Flags_SetEventChkInf(EVENTCHKINF_SHOWED_MIDO_SWORD_SHIELD);
    Flags_SetEventChkInf(EVENTCHKINF_SPOKE_TO_MIDO_AFTER_DEKU_TREES_DEATH);
}
