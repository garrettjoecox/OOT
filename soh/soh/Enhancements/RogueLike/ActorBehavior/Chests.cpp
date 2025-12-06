#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "src/overlays/actors/ovl_En_Box/z_en_box.h"

s32 Player_SetupWaitForPutAway(PlayState* play, Player* player, AfterPutAwayFunc afterPutAwayFunc);
void Player_SetupActionPreserveAnimMovement(PlayState* play, Player* player, PlayerActionFunc actionFunc, s32 flags);
void func_8084DFAC(PlayState* play, Player* player);
}

void Player_Action_8084E6D4_overridden(Player* player, PlayState* play) {
    if (LinkAnimation_Update(play, &player->skelAnime)) {
        // Player_StopCutscene(player); ??
        func_8084DFAC(play, player);

        EnBox* enBox = (EnBox*)player->interactRangeActor;

        RogueLike::XP::SpawnXPGroup(enBox->dyna.actor.world.pos, CVarGetInteger("gRogueLike.XPDrop.Chests", 50));

        Sfx_PlaySfxCentered(NA_SE_SY_GET_RUPY);
    }
}

void func_8083A434_overridden(PlayState* play, Player* player) {
    Player_SetupActionPreserveAnimMovement(play, player, Player_Action_8084E6D4_overridden, 0);
    player->stateFlags1 |= PLAYER_STATE1_GETTING_ITEM | PLAYER_STATE1_IN_CUTSCENE;
}

// This simply prevents the player from getting an item from the chest, but still
// plays the chest opening animation and ensure the treasure chest flag is set
static void InitChestsBehavior() {
    COND_VB_SHOULD(VB_GIVE_ITEM_FROM_CHEST, IS_ROGUELIKE, {
        EnBox* enBox = va_arg(args, EnBox*);
        Actor* actor = (Actor*)enBox;
        Player* player = GET_PLAYER(gPlayState);
        Player_SetupWaitForPutAway(gPlayState, player, func_8083A434_overridden);
        *should = false;
    });

    // Replace the item in the chest with a recovery heart, to prevent any other item side effects
    // COND_ID_HOOK(ShouldActorInit, ACTOR_EN_BOX, IS_ROGUELIKE, [](Actor* actor, bool* should) {
    //     actor->params = ((actor->params & ~(0x7F << 5)) | ((GI_HEART & 0x7F) << 5));
    // });
}

static RegisterShipInitFunc initFunc(InitChestsBehavior, { "IS_ROGUELIKE" });
