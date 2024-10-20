#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>

extern "C" {
#include "macros.h"
#include "variables.h"
extern PlayState* gPlayState;
}

/**
 * PLAYER_UPDATE
 *
 * Contains real-time data necessary to update other clients in the same scene as the player
 *
 * Sent every frame to other clients within the same scene
 *
 * Note: This packet is sent _a lot_, so please do not include any unnecessary data in it
 */

void Anchor::SendPacket_PlayerUpdate() {
    if (!IsSaveLoaded()) {
        return;
    }

    uint32_t currentPlayerCount = 0;
    for (auto& [clientId, client] : clients) {
        if (client.sceneNum == gPlayState->sceneNum) {
            currentPlayerCount++;
        }
    }
    if (currentPlayerCount == 0) {
        return;
    }

    Player* player = GET_PLAYER(gPlayState);
    nlohmann::json payload;

    payload["type"] = PLAYER_UPDATE;
    payload["sceneNum"] = gPlayState->sceneNum;
    payload["entranceIndex"] = gSaveContext.entranceIndex;
    payload["linkAge"] = gSaveContext.linkAge;
    payload["posRot"]["pos"] = player->actor.world.pos;
    payload["posRot"]["rot"] = player->actor.shape.rot;
    payload["jointTable"] = player->jointTable;
    payload["upperLimbRot"] = player->upperLimbRot;
    payload["currentBoots"] = player->currentBoots;
    payload["currentShield"] = player->currentShield;
    payload["currentTunic"] = player->currentTunic;
    payload["stateFlags1"] = player->stateFlags1;
    payload["buttonItem0"] = gSaveContext.equips.buttonItems[0];
    payload["itemAction"] = player->itemAction;
    payload["heldItemAction"] = player->heldItemAction;
    payload["modelGroup"] = player->modelGroup;
    payload["quiet"] = true;

    for (auto& [clientId, client] : clients) {
        if (client.sceneNum == gPlayState->sceneNum) {
            payload["targetClientId"] = clientId;
            SendJsonToRemote(payload);
        }
    }
}

void Anchor::HandlePacket_PlayerUpdate(nlohmann::json payload) {
    uint32_t clientId = payload["clientId"].get<uint32_t>();

    bool shouldRefreshActors = false;

    if (clients.contains(clientId)) {
        auto& client = clients[clientId];

        if (client.linkAge != payload["linkAge"].get<s32>()) {
            shouldRefreshActors = true;
        }

        client.sceneNum = payload["sceneNum"].get<s16>();
        client.entranceIndex = payload["entranceIndex"].get<s32>();
        client.linkAge = payload["linkAge"].get<s32>();
        client.posRot = payload["posRot"].get<PosRot>();
        for (int i = 0; i < 24; i++) {
            client.jointTable[i] = payload["jointTable"][i].get<Vec3s>();
        }
        client.upperLimbRot = payload["upperLimbRot"].get<Vec3s>();
        client.currentBoots = payload["currentBoots"].get<s8>();
        client.currentShield = payload["currentShield"].get<s8>();
        client.currentTunic = payload["currentTunic"].get<s8>();
        client.stateFlags1 = payload["stateFlags1"].get<u32>();
        client.buttonItem0 = payload["buttonItem0"].get<u8>();
        client.itemAction = payload["itemAction"].get<s8>();
        client.heldItemAction = payload["heldItemAction"].get<s8>();
        client.modelGroup = payload["modelGroup"].get<u8>();
    }

    if (shouldRefreshActors) {
        RefreshClientActors();
    }
}

#endif // ENABLE_REMOTE_CONTROL
