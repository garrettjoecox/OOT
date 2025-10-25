#include "ActorBehavior.h"
#include "soh/ShipInit.hpp"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/custom-item/CustomItem.h"

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
       
        // Spawn 1-5 rupees, sending them flying in random directions
        s32 rupeeCount = (Rand_ZeroOne() * 5.0f) + 2.0f;
        for (s32 i = 0; i < rupeeCount; i++) {
            EnItem00* item = CustomItem::Spawn(
                enBox->dyna.actor.world.pos.x, enBox->dyna.actor.world.pos.y + 10.0f, 
                enBox->dyna.actor.world.pos.z, 0, 
                CustomItem::STOP_BOBBING, GID_RUPEE_GREEN,
                [](Actor* actor, PlayState* play) {
                    gSaveContext.ship.quest.data.rogueLike.experiencePoints += 1;
                }, [](Actor* actor, PlayState* play) {
                    Matrix_Scale(10.0f, 10.0f, 10.0f, MTXMODE_APPLY);
                    Matrix_Translate(0.0f, -100.0f, 0.0f, MTXMODE_APPLY);
                    GetItem_Draw(play, CUSTOM_ITEM_PARAM);

                    // Don't let the item get picked up till it hits the ground
                    if (actor->bgCheckFlags & 1) {
                        CUSTOM_ITEM_FLAGS |= CustomItem::KILL_ON_TOUCH;
                    }
                });
           
            item->actor.velocity.y = 8.0f;
            item->actor.speedXZ = (Rand_ZeroOne() * 4.0f) + 1.0f;
            item->actor.gravity = -0.9f;
            item->actor.shape.rot.y = item->actor.world.rot.y = Rand_CenteredFloat(65536.0f);
        }
    }
}

void func_8083A434_overridden(PlayState* play, Player* player) {
    Player_SetupActionPreserveAnimMovement(play, player, Player_Action_8084E6D4_overridden, 0);
    player->stateFlags1 |= PLAYER_STATE1_GETTING_ITEM | PLAYER_STATE1_IN_CUTSCENE;
}

// This simply prevents the player from getting an item from the chest, but still
// plays the chest opening animation and ensure the treasure chest flag is set
void RogueLike::ActorBehavior::InitEnBoxBehavior() {
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
