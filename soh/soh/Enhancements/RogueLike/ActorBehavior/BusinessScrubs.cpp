#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"
#include "overlays/actors/ovl_En_Dns/z_en_dns.h"

extern PlayState* gPlayState;
}

std::set<std::tuple<s16, s8, int16_t>> killedScrubs;

static void InitBusinessScrubsBehavior() {
    killedScrubs.clear();

    COND_ID_HOOK(ShouldActorInit, ACTOR_EN_DNS, IS_ROGUELIKE, [](void* actor, bool* should) {
        EnDns* scrubActor = static_cast<EnDns*>(actor);
        int16_t actorIndex = GetActorListIndex((Actor*)scrubActor);

        *should = false;

        if (actorIndex == -1) {
            actorIndex = scrubActor->actor.home.pos.x + scrubActor->actor.home.pos.z;
        }

        auto tupleKey = std::make_tuple(gPlayState->sceneNum, gPlayState->roomCtx.curRoom.num, actorIndex);

        if (killedScrubs.find(tupleKey) == killedScrubs.end()) {
            RogueLike::XP::SpawnXPGroup(scrubActor->actor.world.pos,
                                        CVarGetInteger("gRogueLike.XPDrop.BusinessScrubs", 100));
            killedScrubs.insert(tupleKey);
        }
    });
}

static RegisterShipInitFunc initFunc(InitBusinessScrubsBehavior, { "IS_ROGUELIKE" });
