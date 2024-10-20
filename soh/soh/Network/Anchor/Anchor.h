#ifdef ENABLE_REMOTE_CONTROL
#ifndef NETWORK_ANCHOR_H
#define NETWORK_ANCHOR_H
#ifdef __cplusplus

#include "soh/Network/Network.h"
#include <libultraship/libultraship.h>

extern "C" {
#include "variables.h"
#include "z64.h"
}

void DummyPlayer_Init(Actor* actor, PlayState* play);
void DummyPlayer_Update(Actor* actor, PlayState* play);
void DummyPlayer_Draw(Actor* actor, PlayState* play);
void DummyPlayer_Destroy(Actor* actor, PlayState* play);

typedef struct {
    uint32_t clientId;
    std::string name;
    Color_RGB8 color;
    std::string clientVersion;
    uint32_t seed;
    bool isSaveLoaded;
    bool isGameComplete;
    s16 sceneNum;
    s32 entranceIndex;

    // Only available in PLAYER_UPDATE packets
    s32 linkAge;
    PosRot posRot;
    Vec3s jointTable[24];
    Vec3s upperLimbRot;
    s8 currentBoots;
    s8 currentShield;
    s8 currentTunic;
    u32 stateFlags1;
    u8 buttonItem0;
    s8 itemAction;
    s8 heldItemAction;
    u8 modelGroup;

    // Ptr to the dummy player
    Player* player;
} AnchorClient;

class Anchor : public Network {
  private:
    bool refreshingActors = false;

    bool IsSaveLoaded();
    void RegisterHooks();
    void RefreshClientActors();
    void HandlePacket_AllClientData(nlohmann::json payload);
    void SendPacket_UpdateClientData();
    void HandlePacket_UpdateClientData(nlohmann::json payload);
    void SendPacket_PlayerUpdate();
    void HandlePacket_PlayerUpdate(nlohmann::json payload);
    void SendPacket_RequestSaveState();
    void HandlePacket_RequestSaveState(nlohmann::json payload);
    void SendPacket_PushSaveState();
    void HandlePacket_PushSaveState(nlohmann::json payload);
    void SendPacket_SetFlag(s16 sceneNum, s16 flagType, s16 flag);
    void HandlePacket_SetFlag(nlohmann::json payload);
    void SendPacket_UnsetFlag(s16 sceneNum, s16 flagType, s16 flag);
    void HandlePacket_UnsetFlag(nlohmann::json payload);
    void SendPacket_SetCheckStatus(RandomizerCheck rc);
    void HandlePacket_SetCheckStatus(nlohmann::json payload);

  public:
    inline static const std::string clientVersion = (char*)gBuildVersion;

    // Packet types //
    inline static const std::string ALL_CLIENT_DATA = "ALL_CLIENT_DATA";
    inline static const std::string UPDATE_CLIENT_DATA = "UPDATE_CLIENT_DATA";
    inline static const std::string PLAYER_UPDATE = "PLAYER_UPDATE";
    inline static const std::string REQUEST_SAVE_STATE = "REQUEST_SAVE_STATE";
    inline static const std::string PUSH_SAVE_STATE = "PUSH_SAVE_STATE";
    inline static const std::string SET_FLAG = "SET_FLAG";
    inline static const std::string UNSET_FLAG = "UNSET_FLAG";
    inline static const std::string SET_CHECK_STATUS = "SET_CHECK_STATUS";

    static Anchor* Instance;
    std::map<uint32_t, AnchorClient> clients;
    std::vector<uint32_t> actorIndexToClientId;

    void Enable();
    void Disable();
    void OnIncomingJson(nlohmann::json payload);
    void OnConnected();
    void OnDisconnected();
    void DrawMenu();
    void SendJsonToRemote(nlohmann::json packet);
};

#endif // __cplusplus
#endif // NETWORK_ANCHOR_H
#endif // ENABLE_REMOTE_CONTROL
