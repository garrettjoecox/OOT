#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>

/**
 * REQUEST_SAVE_STATE
 *
 * Requests a save state from the server, this will be sent to all clients connected, all clients that have a save
 * loaded will emit a PUSH_SAVE_STATE packet, but only the first client to respond will fulfill the request
 *
 * This fires when loading into a file while Anchor is connected, or when Anchor is connected while a file is already
 * loaded
 *
 * Note: This can additionally be fired with a button in the menus to fix any desyncs that may have occurred in the save
 * state
 */

void Anchor::SendPacket_RequestSaveState() {
    nlohmann::json payload;
    payload["type"] = REQUEST_SAVE_STATE;

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_RequestSaveState(nlohmann::json payload) {
    if (!IsSaveLoaded()) {
        return;
    }

    SendPacket_PushSaveState();
}

#endif // ENABLE_REMOTE_CONTROL
