#ifdef ENABLE_REMOTE_CONTROL

#include "soh/Network/Anchor/Anchor.h"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/OTRGlobals.h"

/**
 * SET_CHECK_STATUS
 * 
 * Fired when a check status is updated or skipped
 */

void Anchor::SendPacket_SetCheckStatus(RandomizerCheck rc) {
    if (!IsSaveLoaded()) {
        return;
    }

    auto randoContext = Rando::Context::GetInstance();

    nlohmann::json payload;
    payload["type"] = SET_CHECK_STATUS;
    payload["rc"] = rc;
    payload["status"] = randoContext->GetItemLocation(rc)->GetCheckStatus();
    payload["skipped"] = randoContext->GetItemLocation(rc)->GetIsSkipped();
    payload["quiet"] = true;

    SendJsonToRemote(payload);
}

void Anchor::HandlePacket_SetCheckStatus(nlohmann::json payload) {
    if (!IsSaveLoaded()) {
        return;
    }

    auto randoContext = Rando::Context::GetInstance();

    RandomizerCheck rc = payload["rc"].get<RandomizerCheck>();
    RandomizerCheckStatus status = payload["status"].get<RandomizerCheckStatus>();
    bool skipped = payload["skipped"].get<bool>();

    if (randoContext->GetItemLocation(rc)->GetCheckStatus() != status) {
        randoContext->GetItemLocation(rc)->SetCheckStatus(status);
    }
    if (randoContext->GetItemLocation(rc)->GetIsSkipped() != skipped) {
        randoContext->GetItemLocation(rc)->SetIsSkipped(skipped);
    }
}

#endif // ENABLE_REMOTE_CONTROL
