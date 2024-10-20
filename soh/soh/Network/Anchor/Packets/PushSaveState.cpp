#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/Enhancements/randomizer/entrance.h"
#include "soh/Enhancements/randomizer/dungeon.h"
#include "soh/OTRGlobals.h"

extern "C" {
#include "variables.h"
extern PlayState* gPlayState;
}

/**
 * PUSH_SAVE_STATE
 *
 * Pushes the current save state to the server, this will be sent to any requesting clients
 */

void Anchor::SendPacket_PushSaveState() {
    if (!IsSaveLoaded()) {
        return;
    }

    json payload = gSaveContext;
    payload["type"] = PUSH_SAVE_STATE;
    // manually update current scene flags
    payload["sceneFlags"][gPlayState->sceneNum]["chest"] = gPlayState->actorCtx.flags.chest;
    payload["sceneFlags"][gPlayState->sceneNum]["swch"] = gPlayState->actorCtx.flags.swch;
    payload["sceneFlags"][gPlayState->sceneNum]["clear"] = gPlayState->actorCtx.flags.clear;
    payload["sceneFlags"][gPlayState->sceneNum]["collect"] = gPlayState->actorCtx.flags.collect;

    // The commented out code below is an attempt at sending the entire randomizer seed over, in hopes that a player doesn't have to generate the seed themselves
    // Currently it doesn't work :)
    if (IS_RANDO) {
        auto randoContext = Rando::Context::GetInstance();

        payload["rando"] = json::object();
        payload["rando"]["itemLocations"] = json::array();
        for (int i = 0; i < RC_MAX; i++) {
            payload["rando"]["itemLocations"][i] = json::object();
            // payload["rando"]["itemLocations"][i]["rgID"] = randoContext->GetItemLocation(i)->GetPlacedRandomizerGet();
            payload["rando"]["itemLocations"][i]["status"] = randoContext->GetItemLocation(i)->GetCheckStatus();
            payload["rando"]["itemLocations"][i]["skipped"] = randoContext->GetItemLocation(i)->GetIsSkipped();

            // if (randoContext->GetItemLocation(i)->GetPlacedRandomizerGet() == RG_ICE_TRAP) {
            //     payload["rando"]["itemLocations"][i]["fakeRgID"] = randoContext->GetItemOverride(i).LooksLike();
            //     payload["rando"]["itemLocations"][i]["trickName"] = json::object();
            //     payload["rando"]["itemLocations"][i]["trickName"]["english"] = randoContext->GetItemOverride(i).GetTrickName().GetEnglish();
            //     payload["rando"]["itemLocations"][i]["trickName"]["french"] = randoContext->GetItemOverride(i).GetTrickName().GetFrench();
            // }
            // if (randoContext->GetItemLocation(i)->HasCustomPrice()) {
            //     payload["rando"]["itemLocations"][i]["price"] = randoContext->GetItemLocation(i)->GetPrice();
            // }
        }

        // auto entranceCtx = randoContext->GetEntranceShuffler();
        // for (int i = 0; i < ENTRANCE_OVERRIDES_MAX_COUNT; i++) {
        //     payload["rando"]["entrances"][i] = json::object();
        //     payload["rando"]["entrances"][i]["type"] = entranceCtx->entranceOverrides[i].type;
        //     payload["rando"]["entrances"][i]["index"] = entranceCtx->entranceOverrides[i].index;
        //     payload["rando"]["entrances"][i]["destination"] = entranceCtx->entranceOverrides[i].destination;
        //     payload["rando"]["entrances"][i]["override"] = entranceCtx->entranceOverrides[i].override;
        //     payload["rando"]["entrances"][i]["overrideDestination"] = entranceCtx->entranceOverrides[i].overrideDestination;
        // }

        // payload["rando"]["seed"] = json::array();
        // for (int i = 0; i < randoContext->hashIconIndexes.size(); i++) {
        //     payload["rando"]["seed"][i] = randoContext->hashIconIndexes[i];
        // }
        // payload["rando"]["inputSeed"] = randoContext->GetSettings()->GetSeedString();
        // payload["rando"]["finalSeed"] = randoContext->GetSettings()->GetSeed();
        
        // payload["rando"]["randoSettings"] = json::array();
        // for (int i = 0; i < RSK_MAX; i++) {
        //     payload["rando"]["randoSettings"][i] = randoContext->GetOption((RandomizerSettingKey(i))).GetSelectedOptionIndex();
        // }

        // payload["rando"]["masterQuestDungeonCount"] = randoContext->GetDungeons()->CountMQ();
        // payload["rando"]["masterQuestDungeons"] = json::array();
        // for (int i = 0; i < randoContext->GetDungeons()->GetDungeonListSize(); i++) {
        //     payload["rando"]["masterQuestDungeons"][i] = randoContext->GetDungeon(i)->IsMQ();
        // }
        // for (int i = 0; i < randoContext->GetTrials()->GetTrialListSize(); i++) {
        //     payload["rando"]["requiredTrials"][i] = randoContext->GetTrial(i)->IsRequired();
        // }
    }

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_PushSaveState(nlohmann::json payload) {
    // This can happen in between file select and the game starting, so we cant use this check, but we need to ensure we
    // be careful to wrap PlayState usage in this check
    // if (!IsSaveLoaded()) {
    //     return;
    // }

    SaveContext loadedData = payload.get<SaveContext>();

    gSaveContext.questId = loadedData.questId;
    gSaveContext.healthCapacity = loadedData.healthCapacity;
    gSaveContext.magicLevel = loadedData.magicLevel;
    gSaveContext.magicCapacity = gSaveContext.magic = loadedData.magicCapacity;
    gSaveContext.isMagicAcquired = loadedData.isMagicAcquired;
    gSaveContext.isDoubleMagicAcquired = loadedData.isDoubleMagicAcquired;
    gSaveContext.isDoubleDefenseAcquired = loadedData.isDoubleDefenseAcquired;
    gSaveContext.bgsFlag = loadedData.bgsFlag;
    gSaveContext.swordHealth = loadedData.swordHealth;
    gSaveContext.adultTradeItems = loadedData.adultTradeItems;
    gSaveContext.triforcePiecesCollected = loadedData.triforcePiecesCollected;

    for (int i = 0; i < 124; i++) {
        gSaveContext.sceneFlags[i] = loadedData.sceneFlags[i];
        if (IsSaveLoaded() && gPlayState->sceneNum == i) {
            gPlayState->actorCtx.flags.chest = loadedData.sceneFlags[i].chest;
            gPlayState->actorCtx.flags.swch = loadedData.sceneFlags[i].swch;
            gPlayState->actorCtx.flags.clear = loadedData.sceneFlags[i].clear;
            gPlayState->actorCtx.flags.collect = loadedData.sceneFlags[i].collect;
        }
    }

    for (int i = 0; i < 14; i++) {
        gSaveContext.eventChkInf[i] = loadedData.eventChkInf[i];
    }

    for (int i = 0; i < 4; i++) {
        gSaveContext.itemGetInf[i] = loadedData.itemGetInf[i];
    }

    // Skip last row of infTable, don't want to sync swordless flag
    for (int i = 0; i < 29; i++) {
        gSaveContext.infTable[i] = loadedData.infTable[i];
    }

    for (int i = 0; i < 9; i++) {
        gSaveContext.randomizerInf[i] = loadedData.randomizerInf[i];
    }

    for (int i = 0; i < 6; i++) {
        gSaveContext.gsFlags[i] = loadedData.gsFlags[i];
    }

    gSaveContext.sohStats.fileCreatedAt = loadedData.sohStats.fileCreatedAt;

    // Restore master sword state
    u8 hasMasterSword = CHECK_OWNED_EQUIP(EQUIP_TYPE_SWORD, 1);
    if (hasMasterSword) {
        loadedData.inventory.equipment |= 0x2;
    } else {
        loadedData.inventory.equipment &= ~0x2;
    }

    // Restore bottle contents (unless it's ruto's letter)
    for (int i = 0; i < 4; i++) {
        if (gSaveContext.inventory.items[SLOT_BOTTLE_1 + i] != ITEM_NONE && gSaveContext.inventory.items[SLOT_BOTTLE_1 + i] != ITEM_LETTER_RUTO) {
            loadedData.inventory.items[SLOT_BOTTLE_1 + i] = gSaveContext.inventory.items[SLOT_BOTTLE_1 + i];
        }
    }

    // Restore ammo if it's non-zero, unless it's beans
    for (int i = 0; i < ARRAY_COUNT(gSaveContext.inventory.ammo); i++) {
        if (gSaveContext.inventory.ammo[i] != 0 && i != SLOT(ITEM_BEAN) && i != SLOT(ITEM_BEAN + 1)) {
            loadedData.inventory.ammo[i] = gSaveContext.inventory.ammo[i];
        }
    }

    gSaveContext.inventory = loadedData.inventory;

    // The commented out code below is an attempt at sending the entire randomizer seed over, in hopes that a player doesn't have to generate the seed themselves
    // Currently it doesn't work :)
    if (IS_RANDO && payload.contains("rando")) {
        auto randoContext = Rando::Context::GetInstance();

        for (int i = 0; i < RC_MAX; i++) {
            // randoContext->GetItemLocation(i)->RefPlacedItem() = payload["rando"]["itemLocations"][i]["rgID"].get<RandomizerGet>();
            OTRGlobals::Instance->gRandoContext->GetItemLocation(i)->SetCheckStatus(payload["rando"]["itemLocations"][i]["status"].get<RandomizerCheckStatus>());
            OTRGlobals::Instance->gRandoContext->GetItemLocation(i)->SetIsSkipped(payload["rando"]["itemLocations"][i]["skipped"].get<bool>());

            // if (payload["rando"]["itemLocations"][i].contains("fakeRgID")) {
            //     randoContext->overrides.emplace(static_cast<RandomizerCheck>(i), Rando::ItemOverride(static_cast<RandomizerCheck>(i), payload["rando"]["itemLocations"][i]["fakeRgID"].get<RandomizerGet>()));
            //     randoContext->GetItemOverride(i).GetTrickName().english = payload["rando"]["itemLocations"][i]["trickName"]["english"].get<std::string>();
            //     randoContext->GetItemOverride(i).GetTrickName().french = payload["rando"]["itemLocations"][i]["trickName"]["french"].get<std::string>();
            // }
            // if (payload["rando"]["itemLocations"][i].contains("price")) {
            //     u16 price = payload["rando"]["itemLocations"][i]["price"].get<u16>();
            //     if (price > 0) {
            //         randoContext->GetItemLocation(i)->SetCustomPrice(price);
            //     }
            // }
        }

        // auto entranceCtx = randoContext->GetEntranceShuffler();
        // for (int i = 0; i < ENTRANCE_OVERRIDES_MAX_COUNT; i++) {
        //     entranceCtx->entranceOverrides[i].type = payload["rando"]["entrances"][i]["type"].get<u16>();
        //     entranceCtx->entranceOverrides[i].index = payload["rando"]["entrances"][i]["index"].get<s16>();
        //     entranceCtx->entranceOverrides[i].destination = payload["rando"]["entrances"][i]["destination"].get<s16>();
        //     entranceCtx->entranceOverrides[i].override = payload["rando"]["entrances"][i]["override"].get<s16>();
        //     entranceCtx->entranceOverrides[i].overrideDestination = payload["rando"]["entrances"][i]["overrideDestination"].get<s16>();
        // }

        // for (int i = 0; i < randoContext->hashIconIndexes.size(); i++) {
        //     randoContext->hashIconIndexes[i] = payload["rando"]["seed"][i].get<u8>();
        // }
        // randoContext->GetSettings()->SetSeedString(payload["rando"]["inputSeed"].get<std::string>());
        // randoContext->GetSettings()->SetSeed(payload["rando"]["finalSeed"].get<u32>());

        // for (int i = 0; i < RSK_MAX; i++) {
        //     randoContext->GetOption(RandomizerSettingKey(i)).SetSelectedIndex(payload["rando"]["randoSettings"][i].get<u8>());
        // }

        // randoContext->GetDungeons()->ClearAllMQ();
        // for (int i = 0; i < randoContext->GetDungeons()->GetDungeonListSize(); i++) {
        //     if (payload["rando"]["masterQuestDungeons"][i].get<bool>()) {
        //         randoContext->GetDungeon(i)->SetMQ();
        //     }
        // }
        
        // randoContext->GetTrials()->SkipAll();
        // for (int i = 0; i < randoContext->GetTrials()->GetTrialListSize(); i++) {
        //     if (payload["rando"]["requiredTrials"][i].get<bool>()) {
        //         randoContext->GetTrial(i)->SetAsRequired();
        //     }
        // }
    }
}

#endif // ENABLE_REMOTE_CONTROL
