#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include "soh/Network/Anchor/JsonConversions.hpp"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>

/**
 * ALL_CLIENT_DATA
 *
 * Contains a list of all clients and their CLIENT_DATA currently connected to the server
 *
 * The server itself sends this packet to all clients when a client connects or disconnects
 */

void Anchor::HandlePacket_AllClientData(nlohmann::json payload) {
    std::vector<AnchorClient> newClients = payload["clients"].get<std::vector<AnchorClient>>();

    // add new clients
    for (auto& client : newClients) {
        if (!clients.contains(client.clientId)) {
            clients[client.clientId].name = client.name;
            clients[client.clientId].color = client.color;
            clients[client.clientId].clientVersion = client.clientVersion;
            clients[client.clientId].seed = client.seed;
            clients[client.clientId].isSaveLoaded = client.isSaveLoaded;
            clients[client.clientId].isGameComplete = client.isGameComplete;
            clients[client.clientId].sceneNum = client.sceneNum;
            clients[client.clientId].entranceIndex = client.entranceIndex;
        }
    }

    // remove clients that are no longer in the list
    std::vector<uint32_t> clientsToRemove;
    for (auto& [clientId, client] : clients) {
        if (std::find_if(newClients.begin(), newClients.end(),
                         [clientId](AnchorClient& c) { return c.clientId == clientId; }) == newClients.end()) {
            clientsToRemove.push_back(clientId);
        }
    }
    // (seperate loop to avoid iterator invalidation)
    for (auto& clientId : clientsToRemove) {
        clients.erase(clientId);
    }

    RefreshClientActors();
}

#endif // ENABLE_REMOTE_CONTROL
