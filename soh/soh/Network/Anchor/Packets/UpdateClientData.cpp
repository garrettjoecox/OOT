#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/OTRGlobals.h"

extern "C" {
#include "variables.h"
extern PlayState* gPlayState;
}

/**
 * UPDATE_CLIENT_DATA
 *
 * Contains a small subset of data that is cached on the server and important for the client to know for various reasons
 *
 * Sent on various events, such as changing scenes, soft resetting, finishing the game, opening file select, etc.
 *
 * Note: This packet should be cross version compatible, so if you add anything here don't assume all clients will be
 * providing it, consider doing a `contains` check before accessing any version specific data
 */

void Anchor::SendPacket_UpdateClientData() {
    nlohmann::json payload;
    payload["type"] = UPDATE_CLIENT_DATA;
    payload["data"]["name"] = CVarGetString(CVAR_REMOTE_ANCHOR("Name"), "");
    payload["data"]["color"] = CVarGetColor24(CVAR_REMOTE_ANCHOR("Color"), { 100, 255, 100 });
    payload["data"]["clientVersion"] = clientVersion;

    if (IsSaveLoaded()) {
        payload["data"]["seed"] = IS_RANDO ? Rando::Context::GetInstance()->GetSettings()->GetSeed() : 0;
        payload["data"]["isSaveLoaded"] = true;
        payload["data"]["isGameComplete"] = gSaveContext.sohStats.gameComplete;
        payload["data"]["sceneNum"] = gPlayState->sceneNum;
        payload["data"]["entranceIndex"] = gSaveContext.entranceIndex;
    } else {
        payload["data"]["seed"] = 0;
        payload["data"]["isSaveLoaded"] = false;
        payload["data"]["isGameComplete"] = false;
        payload["data"]["sceneNum"] = SCENE_ID_MAX;
        payload["data"]["entranceIndex"] = 0x00;
    }

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_UpdateClientData(nlohmann::json payload) {
    uint32_t clientId = payload["clientId"].get<uint32_t>();

    if (clients.contains(clientId)) {
        AnchorClient client = payload["data"].get<AnchorClient>();
        clients[clientId].clientId = clientId;
        clients[clientId].name = client.name;
        clients[clientId].color = client.color;
        clients[clientId].clientVersion = client.clientVersion;
        clients[clientId].seed = client.seed;
        clients[clientId].isSaveLoaded = client.isSaveLoaded;
        clients[clientId].isGameComplete = client.isGameComplete;
        clients[clientId].sceneNum = client.sceneNum;
        clients[clientId].entranceIndex = client.entranceIndex;
    }
}

#endif // ENABLE_REMOTE_CONTROL
