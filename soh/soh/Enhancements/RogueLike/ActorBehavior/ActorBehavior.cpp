#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

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
        case VB_OPEN_KOKIRI_FOREST: {
            *should = true;
            break;
        }
        case VB_GIVE_ITEM_FROM_ANJU_AS_ADULT: {
            EnNiwLady* enNiwLady = va_arg(args, EnNiwLady*);
            Flags_SetItemGetInf(ITEMGETINF_2C);
            RogueLike::Quests::AddQuestById(RL_QUEST_HF_STALFOS);
            enNiwLady->actionFunc = func_80ABA778;
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
}

static RegisterShipInitFunc initFunc(InitActorBehavior, { "IS_ROGUELIKE" });