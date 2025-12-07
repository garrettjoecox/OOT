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
        Flags_SetEventChkInf(EVENTCHKINF_OPENED_THE_DOOR_OF_TIME);
        Flags_SetEventChkInf(EVENTCHKINF_SHOWED_MIDO_SWORD_SHIELD);
        Flags_SetEventChkInf(EVENTCHKINF_SPOKE_TO_MIDO_AFTER_DEKU_TREES_DEATH);
    }

    // Pick 4 random rewards for this run, seeded by the filecreatedat
    RogueLike::requiredRewards.clear();
    Random_Init(gSaveContext.ship.stats.fileCreatedAt);
    std::vector<uint32_t> rewards = {
        QUEST_MEDALLION_FOREST, QUEST_MEDALLION_FIRE,   QUEST_MEDALLION_WATER,
        QUEST_MEDALLION_SPIRIT, QUEST_MEDALLION_SHADOW, QUEST_MEDALLION_LIGHT,
        QUEST_KOKIRI_EMERALD,   QUEST_GORON_RUBY,       QUEST_ZORA_SAPPHIRE,
    };

    // Shuffle and pick first 4
    while (RogueLike::requiredRewards.size() < 4) {
        size_t index = Random(0, rewards.size() - 1);
        uint32_t reward = rewards[index];
        rewards.erase(rewards.begin() + index);
        RogueLike::requiredRewards.push_back(reward);
    }
}

static RegisterShipInitFunc
    initFunc([]() { GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>(OnLoadGame); }, {});
