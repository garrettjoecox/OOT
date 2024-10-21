#ifdef ENABLE_REMOTE_CONTROL

#include "Anchor.h"
#include <nlohmann/json.hpp>
#include <libultraship/libultraship.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/OTRGlobals.h"
#include "soh/Enhancements/nametag.h"

extern "C" {
#include "variables.h"
#include "functions.h"
extern PlayState* gPlayState;
}

// MARK: - Overrides

void Anchor::Enable() {
    Network::Enable(CVarGetString(CVAR_REMOTE_ANCHOR("Host"), "anchor.proxysaw.dev"), CVarGetInteger(CVAR_REMOTE_ANCHOR("Port"), 43385));
}

void Anchor::Disable() {
    Network::Disable();

    clients.clear();
    RefreshClientActors();
}

void Anchor::OnConnected() {
    SendPacket_UpdateClientData();
    RegisterHooks();

    if (IsSaveLoaded()) {
        SendPacket_RequestSaveState();
    }
}

void Anchor::OnDisconnected() {
    RegisterHooks();
}

void Anchor::SendJsonToRemote(nlohmann::json payload) {
    if (!isConnected) {
        return;
    }

    payload["roomId"] = CVarGetString(CVAR_REMOTE_ANCHOR("RoomId"), "");
    if (!payload.contains("quiet")) {
        SPDLOG_INFO("[Anchor] Sending payload:\n{}", payload.dump());
    }
    Network::SendJsonToRemote(payload);
}

void Anchor::OnIncomingJson(nlohmann::json payload) {
    // If it doesn't contain a type, it's not a valid payload
    if (!payload.contains("type")) {
        return;
    }

    // If it's not a quiet payload, log it
    if (!payload.contains("quiet")) {
        SPDLOG_INFO("[Anchor] Received payload:\n{}", payload.dump());
    }

    std::string packetType = payload["type"].get<std::string>();

    // Ignore packets from mismatched clients, except for ALL_CLIENT_DATA or UPDATE_CLIENT_DATA
    if (packetType != ALL_CLIENT_DATA && packetType != UPDATE_CLIENT_DATA) {
        if (payload.contains("clientId")) {
            uint32_t clientId = payload["clientId"].get<uint32_t>();
            if (clients.contains(clientId) && clients[clientId].clientVersion != clientVersion) {
                return;
            }
        }
    }

    // packetType here is a string so we can't use a switch statement
    if (packetType == ALL_CLIENT_DATA) {
        HandlePacket_AllClientData(payload);
    } else if (packetType == UPDATE_CLIENT_DATA) {
        HandlePacket_UpdateClientData(payload);
    } else if (packetType == PLAYER_UPDATE) {
        HandlePacket_PlayerUpdate(payload);
    } else if (packetType == REQUEST_SAVE_STATE) {
        HandlePacket_RequestSaveState(payload);
    } else if (packetType == PUSH_SAVE_STATE) {
        HandlePacket_PushSaveState(payload);
    } else if (packetType == SET_FLAG) {
        HandlePacket_SetFlag(payload);
    } else if (packetType == UNSET_FLAG) {
        HandlePacket_UnsetFlag(payload);
    } else if (packetType == SET_CHECK_STATUS) {
        HandlePacket_SetCheckStatus(payload);
    }
}

void Anchor::RegisterHooks() {
    static HOOK_ID onSceneSpawnActorsHookId = 0;
    static HOOK_ID shouldActorInitHookId = 0;
    static HOOK_ID onPlayerUpdateHook = 0;
    static HOOK_ID onLoadGameHook = 0;
    static HOOK_ID onFlagSetHook = 0;
    static HOOK_ID onFlagUnsetHook = 0;
    static HOOK_ID onSceneFlagSetHook = 0;
    static HOOK_ID onSceneFlagUnsetHook = 0;
    static HOOK_ID onSetCheckStatusHook = 0;
    static HOOK_ID onSetSkippedHook = 0;

    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneSpawnActors>(onSceneSpawnActorsHookId);
    GameInteractor::Instance->UnregisterGameHookForID<GameInteractor::ShouldActorInit>(shouldActorInitHookId);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(onPlayerUpdateHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnLoadGame>(onLoadGameHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnFlagSet>(onFlagSetHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnFlagUnset>(onFlagUnsetHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneFlagSet>(onSceneFlagSetHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneFlagUnset>(onSceneFlagUnsetHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnRandoSetCheckStatus>(onSetCheckStatusHook);
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnRandoSetIsSkipped>(onSetSkippedHook);

    onSceneSpawnActorsHookId = 0;
    shouldActorInitHookId = 0;
    onPlayerUpdateHook = 0;
    onLoadGameHook = 0;
    onFlagSetHook = 0;
    onFlagUnsetHook = 0;
    onSceneFlagSetHook = 0;
    onSceneFlagUnsetHook = 0;
    onSetCheckStatusHook = 0;
    onSetSkippedHook = 0;

    if (!isConnected) {
        return;
    }

    onSceneSpawnActorsHookId = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneSpawnActors>([&]() {
        SendPacket_UpdateClientData();

        if (IsSaveLoaded()) {
            RefreshClientActors();
        }
    });

    shouldActorInitHookId = GameInteractor::Instance->RegisterGameHookForID<GameInteractor::ShouldActorInit>(ACTOR_PLAYER, [&](void* actorRef, bool* should) {
        Actor* actor = (Actor*)actorRef;

        if (refreshingActors) {
            // By the time we get here, the actor was already added to the ACTORCAT_PLAYER list, so we need to move it
            Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
            actor->id = ACTOR_EN_OE2;
            actor->category = ACTORCAT_NPC;
            actor->init = DummyPlayer_Init;
            actor->update = DummyPlayer_Update;
            actor->draw = DummyPlayer_Draw;
            actor->destroy = DummyPlayer_Destroy;
        }
    });

    onPlayerUpdateHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([&]() {
        SendPacket_PlayerUpdate();
    });

    onLoadGameHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>([&](s16 fileNum) {
        SendPacket_RequestSaveState();
    });

    onFlagSetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnFlagSet>([&](s16 flagType, s16 flag) {
        SendPacket_SetFlag(SCENE_ID_MAX, flagType, flag);
    });

    onFlagUnsetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnFlagUnset>([&](s16 flagType, s16 flag) {
        SendPacket_UnsetFlag(SCENE_ID_MAX, flagType, flag);
    });

    onSceneFlagSetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneFlagSet>([&](s16 sceneNum, s16 flagType, s16 flag) { 
        SendPacket_SetFlag(sceneNum, flagType, flag);
    });

    onSceneFlagUnsetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneFlagUnset>([&](s16 sceneNum, s16 flagType, s16 flag) {
        SendPacket_UnsetFlag(sceneNum, flagType, flag);
    });

    onSetCheckStatusHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnRandoSetCheckStatus>([&](RandomizerCheck rc, RandomizerCheckStatus status) {
        SendPacket_SetCheckStatus(rc);
    });

    onSetSkippedHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnRandoSetIsSkipped>([&](RandomizerCheck rc, bool isSkipped) {
        SendPacket_SetCheckStatus(rc);
    });
}

// MARK: - Misc/Helpers

// Kills all existing anchor actors and respawns them with the new client data
void Anchor::RefreshClientActors() {
    if (!IsSaveLoaded()) {
        return;
    }

    Actor* actor = gPlayState->actorCtx.actorLists[ACTORCAT_NPC].head;

    while (actor != NULL) {
        if (actor->id == ACTOR_EN_OE2 && actor->update == DummyPlayer_Update) {
            NameTag_RemoveAllForActor(actor);
            Actor_Kill(actor);
        }
        actor = actor->next;
    }

    actorIndexToClientId.clear();
    refreshingActors = true;
    for (auto [clientId, client] : clients) {
        actorIndexToClientId.push_back(clientId);
        // We are using a hook `ShouldActorInit` to override the init/update/draw/destroy functions of the Player we spawn
        // We quickly store a mapping of "index" to clientId, then within the init function we use this to get the clientId
        // and store it on player->zTargetActiveTimer (unused s32 for the dummy) for convenience
        auto dummy = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_PLAYER, client.posRot.pos.x,
                                 client.posRot.pos.y, client.posRot.pos.z, client.posRot.rot.x, client.posRot.rot.y,
                                 client.posRot.rot.z, actorIndexToClientId.size() - 1, false);
    }
    refreshingActors = false;
}

bool Anchor::IsSaveLoaded() {
    if (gPlayState == nullptr) {
        return false;
    }

    if (GET_PLAYER(gPlayState) == nullptr) {
        return false;
    }

    if (gSaveContext.fileNum < 0 || gSaveContext.fileNum > 2) {
        return false;
    }

    if (gSaveContext.gameMode != GAMEMODE_NORMAL) {
        return false;
    }

    return true;
}

// MARK: - UI

void Anchor::DrawMenu() {
    ImGui::PushID("Anchor");

    static std::string host = CVarGetString(CVAR_REMOTE_ANCHOR("Host"), "anchor.proxysaw.dev");
    static uint16_t port = CVarGetInteger(CVAR_REMOTE_ANCHOR("Port"), 43385);
    static std::string anchorRoomId = CVarGetString(CVAR_REMOTE_ANCHOR("RoomId"), "");
    static std::string anchorName = CVarGetString(CVAR_REMOTE_ANCHOR("Name"), "");
    bool isFormValid = !SohUtils::IsStringEmpty(host) && port > 1024 && port < 65535 &&
        !SohUtils::IsStringEmpty(anchorRoomId) && !SohUtils::IsStringEmpty(anchorName);

    ImGui::SeparatorText("Anchor");
    // UIWidgets::Tooltip("Anchor Stuff");
    if (ImGui::IsItemClicked()) {
        // ImGui::SetClipboardText("https://github.com/HarbourMasters/sail");
    }

    ImGui::BeginDisabled(isEnabled);
    ImGui::Text("Host & Port");
    if (UIWidgets::InputString("##Host", &host)) {
        CVarSetString(CVAR_REMOTE_ANCHOR("Host"), host.c_str());
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
    }

    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 5);
    if (ImGui::InputScalar("##Port", ImGuiDataType_U16, &port)) {
        CVarSetInteger(CVAR_REMOTE_ANCHOR("Port"), port);
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
    }

    ImGui::Text("Tunic Color & Name");
    static Color_RGBA8 color = CVarGetColor(CVAR_REMOTE_ANCHOR("Color"), { 100, 255, 100, 255 });
    static ImVec4 colorVec = ImVec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, 1);
    if (ImGui::ColorEdit3("##Color", (float*)&colorVec,
                          ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
        color.r = colorVec.x * 255.0;
        color.g = colorVec.y * 255.0;
        color.b = colorVec.z * 255.0;

        CVarSetColor(CVAR_REMOTE_ANCHOR("Color"), color);
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    if (UIWidgets::InputString("##Name", &anchorName)) {
        CVarSetString(CVAR_REMOTE_ANCHOR("Name"), anchorName.c_str());
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
    }
    ImGui::Text("Room ID");
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
    if (UIWidgets::InputString("##RoomId", &anchorRoomId, isEnabled ? ImGuiInputTextFlags_Password : 0)) {
        CVarSetString(CVAR_REMOTE_ANCHOR("RoomId"), anchorRoomId.c_str());
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
    }
    ImGui::EndDisabled();

    ImGui::Spacing();

    ImGui::BeginDisabled(!isFormValid);
    const char* buttonLabel = isEnabled ? "Disable" : "Enable";
    if (ImGui::Button(buttonLabel, ImVec2(-1.0f, 0.0f))) {
        if (isEnabled) {
            CVarClear(CVAR_REMOTE_ANCHOR("Enabled"));
            Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
            Disable();
        } else {
            CVarSetInteger(CVAR_REMOTE_ANCHOR("Enabled"), 1);
            Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesOnNextTick();
            Enable();
        }
    }
    ImGui::EndDisabled();

    if (isEnabled) {
        ImGui::Spacing();
        if (isConnected) {
            ImGui::Text("Connected");

            ImGui::Text("Players in Room:");
            ImGui::Text("%s - %s", CVarGetString(CVAR_REMOTE_ANCHOR("Name"), ""), gPlayState == NULL ? "N/A" : SohUtils::GetSceneName(gPlayState->sceneNum).c_str());
            for (auto& [clientId, client] : Anchor::clients) {
                ImGui::Text("%s - %s", client.name.c_str(), SohUtils::GetSceneName(client.sceneNum).c_str());
                // if (client.clientVersion != Anchor::clientVersion) {
                //     ImGui::SameLine();
                //     ImGui::TextColored(ImVec4(1, 0, 0, 1), ICON_FA_EXCLAMATION_TRIANGLE);
                //     if (ImGui::IsItemHovered()) {
                //         ImGui::BeginTooltip();
                //         ImGui::Text("Incompatible version! Will not work together!");
                //         ImGui::Text("Yours: %s", Anchor::clientVersion.c_str());
                //         ImGui::Text("Theirs: %s", client.clientVersion.c_str());
                //         ImGui::EndTooltip();
                //     }
                // }
                // if (client.seed != gSaveContext.finalSeed && client.fileNum != 0xFF && gSaveContext.fileNum != 0xFF)
                // {
                //     ImGui::SameLine();
                //     ImGui::TextColored(ImVec4(1, 0, 0, 1), ICON_FA_EXCLAMATION_TRIANGLE);
                //     if (ImGui::IsItemHovered()) {
                //         ImGui::BeginTooltip();
                //         ImGui::Text("Seed mismatch! Continuing will break things!");
                //         ImGui::Text("Yours: %u", gSaveContext.finalSeed);
                //         ImGui::Text("Theirs: %u", client.seed);
                //         ImGui::EndTooltip();
                //     }
                // }
            }
        } else {
            ImGui::Text("Connecting...");
        }
    }

    ImGui::PopID();
}

#endif
