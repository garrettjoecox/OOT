#ifdef ENABLE_REMOTE_CONTROL

#include "Anchor.h"
#include "soh/Enhancements/nametag.h"

extern "C" {
#include "variables.h"
#include "functions.h"
extern PlayState* gPlayState;

void Player_UseItem(PlayState* play, Player* player, s32 item);
void Player_DrawGameplay(PlayState* play, Player* player, s32 lod, Gfx* cullDList, OverrideLimbDrawOpa overrideLimbDraw);
}

// Hijacking player->zTargetActiveTimer (unused s32 for the dummy) to store the clientId for convenience
#define DUMMY_CLIENT_ID player->zTargetActiveTimer

void DummyPlayer_Init(Actor* actor, PlayState* play) {
    Player* player = (Player*)actor;

    uint32_t clientId = Anchor::Instance->actorIndexToClientId[actor->params];
    DUMMY_CLIENT_ID = clientId;

    if (!Anchor::Instance->clients.contains(DUMMY_CLIENT_ID)) {
        Actor_Kill(actor);
        return;
    }

    AnchorClient& client = Anchor::Instance->clients[DUMMY_CLIENT_ID];

    // Hack to account for usage of gSaveContext in Player_Init
    s32 originalAge = gSaveContext.linkAge;
    gSaveContext.linkAge = client.linkAge;

    // #region modeled after EnTorch2_Init and Player_Init
    actor->room = -1;
    player->itemAction = player->heldItemAction = -1;
    player->heldItemId = ITEM_NONE;
    Player_UseItem(play, player, ITEM_NONE);
    Player_SetModelGroup(player, Player_ActionToModelGroup(player, player->heldItemAction));
    play->playerInit(player, play, gPlayerSkelHeaders[client.linkAge]);

    play->func_11D54(player, play);
    // #endregion

    gSaveContext.linkAge = originalAge;

    NameTag_RegisterForActorWithOptions(actor, client.name.c_str(), { .yOffset = 30 });
}

void Math_Vec3s_Copy(Vec3s* dest, Vec3s* src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}

// Update the actor with new data from the client
void DummyPlayer_Update(Actor* actor, PlayState* play) {
    Player* player = (Player*)actor;

    if (!Anchor::Instance->clients.contains(DUMMY_CLIENT_ID)) {
        Actor_Kill(actor);
        return;
    }

    AnchorClient& client = Anchor::Instance->clients[DUMMY_CLIENT_ID];

    if (client.sceneNum != gPlayState->sceneNum) {
        actor->world.pos.x = -9999.0f;
        actor->world.pos.y = -9999.0f;
        actor->world.pos.z = -9999.0f;
        return;
    }

    Math_Vec3s_Copy(&player->upperLimbRot, &client.upperLimbRot);
    Math_Vec3s_Copy(&actor->shape.rot, &client.posRot.rot);
    Math_Vec3f_Copy(&actor->world.pos, &client.posRot.pos);
    player->skelAnime.jointTable = client.jointTable;
    player->currentBoots = client.currentBoots;
    player->currentShield = client.currentShield;
    player->currentTunic = client.currentTunic;
    player->stateFlags1 = client.stateFlags1;
    player->itemAction = client.itemAction;
    player->heldItemAction = client.heldItemAction;

    if (player->modelGroup != client.modelGroup) {
        // Hack to account for usage of gSaveContext
        s32 originalAge = gSaveContext.linkAge;
        gSaveContext.linkAge = client.linkAge;
        u8 originalButtonItem0 = gSaveContext.equips.buttonItems[0];
        gSaveContext.equips.buttonItems[0] = client.buttonItem0;
        Player_SetModelGroup(player, client.modelGroup);
        gSaveContext.linkAge = originalAge;
        gSaveContext.equips.buttonItems[0] = originalButtonItem0;
    }
}

void DummyPlayer_Draw(Actor* actor, PlayState* play) {
    Player* player = (Player*)actor;

    if (!Anchor::Instance->clients.contains(DUMMY_CLIENT_ID)) {
        Actor_Kill(actor);
        return;
    }

    AnchorClient& client = Anchor::Instance->clients[DUMMY_CLIENT_ID];

    if (client.sceneNum != gPlayState->sceneNum) {
        return;
    }

    // Hack to account for usage of gSaveContext in Player_Draw
    s32 originalAge = gSaveContext.linkAge;
    gSaveContext.linkAge = client.linkAge;
    u8 originalButtonItem0 = gSaveContext.equips.buttonItems[0];
    gSaveContext.equips.buttonItems[0] = client.buttonItem0;
    Player_DrawGameplay(play, player, 0, gCullBackDList, Player_OverrideLimbDrawGameplayDefault);
    gSaveContext.linkAge = originalAge;
    gSaveContext.equips.buttonItems[0] = originalButtonItem0;
}

void DummyPlayer_Destroy(Actor* actor, PlayState* play) {
}

#endif // ENABLE_REMOTE_CONTROL
