#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/Notification/Notification.h"

extern "C" {
#include "variables.h"

// Quest Includes
#include "overlays/actors/ovl_En_Niw_Lady/z_en_niw_lady.h"
void func_80ABA778(EnNiwLady* thisx, PlayState* play);
}

// This is kind of a catch-all for things that are simple enough to not need their own file.
static void MiscVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, va_list originalArgs) {
    va_list args;
    va_copy(args, originalArgs);

    switch (id) {
        case VB_GIVE_ITEM_MINUET_OF_FOREST:
        case VB_GIVE_ITEM_BOLERO_OF_FIRE:
        case VB_GIVE_ITEM_SERENADE_OF_WATER:
        case VB_GIVE_ITEM_REQUIEM_OF_SPIRIT:
        case VB_GIVE_ITEM_NOCTURNE_OF_SHADOW:
        case VB_GIVE_ITEM_PRELUDE_OF_LIGHT:
        case VB_GIVE_ITEM_ZELDAS_LULLABY:
        case VB_GIVE_ITEM_EPONAS_SONG:
        case VB_GIVE_ITEM_SARIAS_SONG:
        case VB_GIVE_ITEM_SUNS_SONG:
        case VB_GIVE_ITEM_SONG_OF_TIME:
        case VB_GIVE_ITEM_SONG_OF_STORMS:
        case VB_GIVE_ITEM_FROM_TARGET_IN_WOODS:
        case VB_GIVE_ITEM_FROM_TALONS_CHICKENS:
        case VB_GIVE_ITEM_FROM_DIVING_MINIGAME:
        case VB_GIVE_ITEM_FROM_GORON:
        case VB_GIVE_ITEM_FROM_LAB_DIVE:
        case VB_GIVE_ITEM_FROM_SKULL_KID_SARIAS_SONG:
        case VB_GIVE_ITEM_FROM_MAN_ON_ROOF:
        case VB_GIVE_ITEM_FAIRY_OCARINA:
        case VB_GIVE_ITEM_WEIRD_EGG:
        case VB_GIVE_ITEM_STRENGTH_1:
        case VB_GIVE_ITEM_ZELDAS_LETTER:
        case VB_GIVE_ITEM_OCARINA_OF_TIME:
        case VB_CHEST_USE_ICE_EFFECT:
            *should = false;
            break;
        case VB_OPEN_KOKIRI_FOREST: {
            *should = true;
            break;
        }
        case VB_BE_ELIGIBLE_FOR_RAINBOW_BRIDGE: {
            *should = true;
            break;
        }
        case VB_GIVE_ITEM_LIGHT_ARROW: {
            if (!gSaveContext.inventory.dungeonItems[SCENE_GANONS_TOWER]) {
                Notification::Emit({
                    .message = "You obtained Ganon's Boss Key!",
                });
                gSaveContext.inventory.dungeonItems[SCENE_GANONS_TOWER] |= 1;
            }
            *should = false;
            break;
        }
        case VB_BE_ELIGIBLE_FOR_LIGHT_ARROWS: {
            *should = true;

            for (uint32_t reward : RogueLike::requiredRewards) {
                if (!CHECK_QUEST_ITEM(reward)) {
                    *should = false;
                }
            }

            break;
        }
        case VB_GIVE_ITEM_FROM_ANJU_AS_ADULT: {
            EnNiwLady* enNiwLady = va_arg(args, EnNiwLady*);
            Flags_SetItemGetInf(ITEMGETINF_2C);
            RogueLike::Quests::AddQuestById(RL_QUEST_KV_STALFOS);
            enNiwLady->actionFunc = func_80ABA778;
            *should = false;
            break;
        }
        case VB_GIVE_ITEM_FROM_ANJU_AS_CHILD: {
            Flags_SetItemGetInf(ITEMGETINF_0C);
            *should = false;
            break;
        }
        default:
            break;
    }
}

static void OnEnemyDefeatHandler(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    switch (actor->id) {
        default:
            RogueLike::XP::SpawnXPGroup(actor->world.pos, CVarGetInteger("gRogueLike.XPDrop.Enemies", 50));
            break;
    }
}

static void InitActorBehavior() {
    COND_HOOK(OnEnemyDefeat, IS_ROGUELIKE, OnEnemyDefeatHandler);
    COND_HOOK(OnVanillaBehavior, IS_ROGUELIKE, MiscVanillaBehaviorHandler);

    COND_ID_HOOK(ShouldActorInit, ACTOR_DEMO_KEKKAI, IS_ROGUELIKE, [](void* actorRef, bool* should) {
        // Prevent the barrier from initializing in Roguelike mode
        *should = false;
    });
}

static RegisterShipInitFunc initFunc(InitActorBehavior, { "IS_ROGUELIKE" });