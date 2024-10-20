#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"

extern "C" {
#include "macros.h"
#include "functions.h"
extern PlayState* gPlayState;
void func_80838280(Player* player);
}

/**
 * DAMAGE_PLAYER
 */

void Anchor::SendPacket_DamagePlayer(u32 clientId, u8 damageEffect, u8 damage) {
    if (!IsSaveLoaded()) {
        return;
    }

    nlohmann::json payload;
    payload["type"] = DAMAGE_PLAYER;
    payload["targetClientId"] = clientId;
    payload["damageEffect"] = damageEffect;
    payload["damage"] = damage;

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_DamagePlayer(nlohmann::json payload) {
    uint32_t clientId = payload["clientId"].get<uint32_t>();
    if (!clients.contains(clientId) || clients[clientId].player == nullptr) {
        return;
    }

    AnchorClient& anchorClient = clients[clientId];
    Player* otherPlayer = anchorClient.player;
    Player* self = GET_PLAYER(gPlayState);

    u8 damageEffect = payload["damageEffect"].get<u8>();
    u8 damage = payload["damage"].get<u8>();

    self->actor.colChkInfo.damage = damage;

    func_80837C0C(gPlayState, self, damageEffect, 4.0f, 5.0f, Actor_WorldYawTowardActor(&otherPlayer->actor, &self->actor), 20);
}

#endif // ENABLE_REMOTE_CONTROL
