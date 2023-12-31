#include <libultraship/bridge.h>
#include "soh/OTRGlobals.h"
#include "soh/Enhancements/enhancementTypes.h"
#include "soh/Enhancements/custom-message/CustomMessageTypes.h"
#include "soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"

extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
#include "src/overlays/actors/ovl_En_Si/z_en_si.h"
#include "src/overlays/actors/ovl_En_Cow/z_en_cow.h"
#include "src/overlays/actors/ovl_En_Shopnuts/z_en_shopnuts.h"
#include "src/overlays/actors/ovl_En_Dns/z_en_dns.h"
extern SaveContext gSaveContext;
extern PlayState* gPlayState;
}

#define RAND_GET_OPTION(option) Rando::Context::GetInstance()->GetOption(option).GetSelectedOptionIndex()

RandomizerCheck GetRandomizerCheckFromFlag(int16_t flagType, int16_t flag) {
    for (auto& loc : Rando::StaticData::GetLocationTable()) {
        if (
            (loc.GetCollectionCheck().flag == flag && (
                (flagType == FLAG_EVENT_CHECK_INF && loc.GetCollectionCheck().type == SPOILER_CHK_EVENT_CHK_INF) ||
                (flagType == FLAG_RANDOMIZER_INF && loc.GetCollectionCheck().type == SPOILER_CHK_RANDOMIZER_INF)
            ) ||
            (loc.GetActorParams() == flag && flagType == FLAG_GS_TOKEN && loc.GetCollectionCheck().type == SPOILER_CHK_GOLD_SKULLTULA)
        )
        ) {
            return loc.GetRandomizerCheck();
        }
    }

    return RC_UNKNOWN_CHECK;
}

RandomizerCheck GetRandomizerCheckFromSceneFlag(int16_t sceneNum, int16_t flagType, int16_t flag) {
    for (auto& loc : Rando::StaticData::GetLocationTable()) {
        if (loc.GetCollectionCheck().scene == sceneNum && loc.GetCollectionCheck().flag == flag && (
            (flagType == FLAG_SCENE_TREASURE && loc.GetCollectionCheck().type == SPOILER_CHK_CHEST) ||
            (flagType == FLAG_SCENE_COLLECTIBLE && loc.GetCollectionCheck().type == SPOILER_CHK_COLLECTABLE) ||
            (flagType == FLAG_GS_TOKEN && loc.GetCollectionCheck().type == SPOILER_CHK_GOLD_SKULLTULA)
        )) {
            return loc.GetRandomizerCheck();
        }
    }

    return RC_UNKNOWN_CHECK;
}

bool MeetsLACSRequirements() {
    switch (RAND_GET_OPTION(RSK_GANONS_BOSS_KEY)) {
        case RO_GANON_BOSS_KEY_LACS_STONES:
            if ((CheckStoneCount() + CheckLACSRewardCount()) >= RAND_GET_OPTION(RSK_LACS_STONE_COUNT)) {
                return true;
            }
            break;
        case RO_GANON_BOSS_KEY_LACS_MEDALLIONS:
            if ((CheckMedallionCount() + CheckLACSRewardCount()) >= RAND_GET_OPTION(RSK_LACS_MEDALLION_COUNT)) {
                return true;
            }
            break;
        case RO_GANON_BOSS_KEY_LACS_REWARDS:
            if ((CheckMedallionCount() + CheckStoneCount() + CheckLACSRewardCount()) >= RAND_GET_OPTION(RSK_LACS_REWARD_COUNT)) {
                return true;
            }
            break;
        case RO_GANON_BOSS_KEY_LACS_DUNGEONS:
            if ((CheckDungeonCount() + CheckLACSRewardCount()) >= RAND_GET_OPTION(RSK_LACS_DUNGEON_COUNT)) {
                return true;
            }
            break;
        case RO_GANON_BOSS_KEY_LACS_TOKENS:
            if (gSaveContext.inventory.gsTokens >= RAND_GET_OPTION(RSK_LACS_TOKEN_COUNT)) {
                return true;
            }
            break;
        default:
            if (CHECK_QUEST_ITEM(QUEST_MEDALLION_SPIRIT) && CHECK_QUEST_ITEM(QUEST_MEDALLION_SHADOW)) {
                return true;
            }
            break;
    }

    return false;
}

// Todo Move this to randomizer context, clear it out on save load etc
static std::queue<RandomizerCheck> randomizerQueuedChecks;
static RandomizerCheck randomizerQueuedCheck = RC_UNKNOWN_CHECK;
static GetItemEntry randomizerQueuedItemEntry = GET_ITEM_NONE;

void RandomizerOnFlagSetHandler(int16_t flagType, int16_t flag) {
    RandomizerCheck rc = GetRandomizerCheckFromFlag(flagType, flag);
    if (rc == RC_UNKNOWN_CHECK) return;

    auto loc = Rando::Context::GetInstance()->GetItemLocation(rc);
    if (loc == nullptr || loc->HasObtained()) return;

    SPDLOG_INFO("Queuing RC: {}", rc);
    randomizerQueuedChecks.push(rc);
}

void RandomizerOnSceneFlagSetHandler(int16_t sceneNum, int16_t flagType, int16_t flag) {
    RandomizerCheck rc = GetRandomizerCheckFromSceneFlag(sceneNum, flagType, flag);
    if (rc == RC_UNKNOWN_CHECK) return;

    auto loc = Rando::Context::GetInstance()->GetItemLocation(rc);
    if (loc == nullptr || loc->HasObtained()) return;

    SPDLOG_INFO("Queuing RC: {}", rc);
    randomizerQueuedChecks.push(rc);
}

static Vec3f spawnPos = { 0.0f, -999.0f, 0.0f };

void RandomizerOnPlayerUpdateForRCQueueHandler() {
    // If we're already queued, don't queue again
    if (randomizerQueuedCheck != RC_UNKNOWN_CHECK) return;

    // If there's nothing to queue, don't queue
    if (randomizerQueuedChecks.size() < 1) return;

    // If we're in a cutscene, don't queue
    Player* player = GET_PLAYER(gPlayState);
    if (Player_InBlockingCsMode(gPlayState, player) || player->stateFlags1 & PLAYER_STATE1_IN_ITEM_CS || player->stateFlags1 & PLAYER_STATE1_GETTING_ITEM || player->stateFlags1 & PLAYER_STATE1_ITEM_OVER_HEAD) {
        return;
    }

    RandomizerCheck rc = randomizerQueuedChecks.front();
    auto loc = Rando::Context::GetInstance()->GetItemLocation(rc);
    GetItemEntry getItemEntry = Rando::Context::GetInstance()->GetFinalGIEntry(rc, true, (GetItemID)Rando::StaticData::GetLocation(rc)->GetVanillaItem());

    if (loc->HasObtained()) {
        SPDLOG_INFO("RC {} already obtained, skipping", rc);
    } else {
        randomizerQueuedCheck = rc;
        randomizerQueuedItemEntry = getItemEntry;
        SPDLOG_INFO("Queueing Item mod {} item {} from RC {}", getItemEntry.modIndex, getItemEntry.itemId, rc);
        if (
            // Skipping ItemGet animation incompatible with checks that require closing a text box to finish
            rc != RC_HF_OCARINA_OF_TIME_ITEM &&
            rc != RC_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST &&
            // Always show ItemGet animation for ice traps
            !(getItemEntry.modIndex == MOD_RANDOMIZER && getItemEntry.getItemId == RG_ICE_TRAP) &&
            (
                CVarGetInteger("gTimeSavers.SkipGetItemAnimation", SGIA_DISABLED) == SGIA_ALL ||
                (
                    CVarGetInteger("gTimeSavers.SkipGetItemAnimation", SGIA_DISABLED) == SGIA_JUNK &&
                    (
                        getItemEntry.getItemCategory == ITEM_CATEGORY_JUNK ||
                        getItemEntry.getItemCategory == ITEM_CATEGORY_SKULLTULA_TOKEN ||
                        getItemEntry.getItemCategory == ITEM_CATEGORY_LESSER
                    )
                )
            )
        ) {
            Item_DropCollectible(gPlayState, &spawnPos, ITEM00_SOH_GIVE_ITEM_ENTRY | 0x8000);
        }
    }

    randomizerQueuedChecks.pop();
}

void RandomizerOnPlayerUpdateForItemQueueHandler() {
    if (randomizerQueuedCheck == RC_UNKNOWN_CHECK) return;

    Player* player = GET_PLAYER(gPlayState);
    if (player == NULL || Player_InBlockingCsMode(gPlayState, player) || player->stateFlags1 & PLAYER_STATE1_IN_ITEM_CS || player->stateFlags1 & PLAYER_STATE1_GETTING_ITEM || player->stateFlags1 & PLAYER_STATE1_ITEM_OVER_HEAD) {
        return;
    }

    SPDLOG_INFO("Attempting to give Item mod {} item {} from RC {}", randomizerQueuedItemEntry.modIndex, randomizerQueuedItemEntry.itemId, randomizerQueuedCheck);
    GiveItemEntryWithoutActor(gPlayState, randomizerQueuedItemEntry);
    if (player->stateFlags1 & PLAYER_STATE1_IN_WATER) {
        // Allow the player to receive the item while swimming
        player->stateFlags2 |= PLAYER_STATE2_UNDERWATER;
        func_8083E5A8(player, gPlayState);
    }
}

void RandomizerOnItemReceiveHandler(GetItemEntry receivedItemEntry) {
    if (randomizerQueuedCheck == RC_UNKNOWN_CHECK) return;

    auto loc = Rando::Context::GetInstance()->GetItemLocation(randomizerQueuedCheck);
    if (randomizerQueuedItemEntry.modIndex == receivedItemEntry.modIndex && randomizerQueuedItemEntry.itemId == receivedItemEntry.itemId) {
        SPDLOG_INFO("Item received mod {} item {} from RC {}", receivedItemEntry.modIndex, receivedItemEntry.itemId, randomizerQueuedCheck);
        loc->MarkAsObtained();
        randomizerQueuedCheck = RC_UNKNOWN_CHECK;
        randomizerQueuedItemEntry = GET_ITEM_NONE;
    }

    if (loc->GetRandomizerCheck() == RC_SPIRIT_TEMPLE_SILVER_GAUNTLETS_CHEST) {
        static uint32_t updateHook;
        updateHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
            Player* player = GET_PLAYER(gPlayState);
            if (player == NULL || Player_InBlockingCsMode(gPlayState, player) || player->stateFlags1 & PLAYER_STATE1_IN_ITEM_CS || player->stateFlags1 & PLAYER_STATE1_GETTING_ITEM || player->stateFlags1 & PLAYER_STATE1_ITEM_OVER_HEAD) {
                return;
            }

            gPlayState->nextEntranceIndex = ENTR_DESERT_COLOSSUS_0;
            gPlayState->transitionTrigger = TRANS_TRIGGER_START;
            gSaveContext.nextCutsceneIndex = 0xFFF1;
            gPlayState->transitionType = TRANS_TYPE_SANDSTORM_END;
            GET_PLAYER(gPlayState)->stateFlags1 &= ~PLAYER_STATE1_IN_CUTSCENE;
            Player_TryCsAction(gPlayState, NULL, 8);
            GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(updateHook);
        });
    }
}

void EnItem00_DrawRandomizedItem(EnItem00* enItem00, PlayState* play) {
    f32 mtxScale = 15.67f;
    Matrix_Scale(mtxScale, mtxScale, mtxScale, MTXMODE_APPLY);
    EnItem00_CustomItemsParticles(&enItem00->actor, play, enItem00->itemEntry);
    GetItemEntry_Draw(play, enItem00->itemEntry);
}

void EnCow_MoveForRandomizer(EnCow* enCow, PlayState* play) {
    bool moved = false;

    // Don't reposition the tail
    if (enCow->actor.params != 0) {
        return;
    }

    // Move left cow in lon lon tower
    if (play->sceneNum == SCENE_LON_LON_BUILDINGS && enCow->actor.world.pos.x == -108 &&
        enCow->actor.world.pos.z == -65) {
        enCow->actor.world.pos.x = -229.0f;
        enCow->actor.world.pos.z = 157.0f;
        enCow->actor.shape.rot.y = 15783.0f;
        moved = true;
        // Move right cow in lon lon stable
    } else if (play->sceneNum == SCENE_STABLE && enCow->actor.world.pos.x == -3 && enCow->actor.world.pos.z == -254) {
        enCow->actor.world.pos.x += 119.0f;
        moved = true;
    }

    if (moved) {
        // Reposition collider
        func_809DEE9C(enCow);
    }
}

void RandomizerOnVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, void* optionalArg) {
    switch (id) {
        case GI_VB_GIVE_ITEM_FROM_CHEST: {
            Player* player = GET_PLAYER(gPlayState);
            player->unk_850 = 1;
            player->getItemId = GI_NONE;
            player->getItemEntry = GetItemEntry(GET_ITEM_NONE);
            *should = false;
            break;
        }
        case GI_VB_PLAY_NABOORU_CAPTURED_CS:
            // This behavior is replicated for randomizer in RandomizerOnItemReceiveHandler
            *should = false;
            break;
        case GI_VB_BE_ELIGIBLE_FOR_SERENADE_OF_WATER:
            *should = !Flags_GetEventChkInf(EVENTCHKINF_LEARNED_SERENADE_OF_WATER) && Flags_GetTreasure(gPlayState, 0x2);
            break;
        case GI_VB_BE_ELIGIBLE_FOR_PRELUDE_OF_LIGHT:
            *should = !Flags_GetEventChkInf(EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT) && CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST);
            break;
        case GI_VB_MOVE_MIDO_IN_KOKIRI_FOREST:
            if (RAND_GET_OPTION(RSK_FOREST) == RO_FOREST_OPEN) {
                *should = true;
            }
            break;
        case GI_VB_MIDO_CONSIDER_DEKU_TREE_DEAD:
            *should = Flags_GetEventChkInf(EVENTCHKINF_OBTAINED_KOKIRI_EMERALD_DEKU_TREE_DEAD);
            break;
        case GI_VB_OPEN_KOKIRI_FOREST:
            *should = Flags_GetEventChkInf(EVENTCHKINF_OBTAINED_KOKIRI_EMERALD_DEKU_TREE_DEAD) || RAND_GET_OPTION(RSK_FOREST) != RO_FOREST_CLOSED;
            break;
        case GI_VB_BE_ELIGIBLE_FOR_DARUNIAS_JOY_REWARD:
            *should = !Flags_GetRandomizerInf(RAND_INF_DARUNIAS_JOY);
            break;
        case GI_VB_BE_ELIGIBLE_FOR_LIGHT_ARROWS:
            *should = !Flags_GetEventChkInf(EVENTCHKINF_RETURNED_TO_TEMPLE_OF_TIME_WITH_ALL_MEDALLIONS) && MeetsLACSRequirements();
            break;
        case GI_VB_BE_ELIGIBLE_FOR_NOCTURNE_OF_SHADOW:
            *should =
                    !Flags_GetEventChkInf(EVENTCHKINF_BONGO_BONGO_ESCAPED_FROM_WELL) &&
                    LINK_IS_ADULT &&
                    gEntranceTable[((void)0, gSaveContext.entranceIndex)].scene == SCENE_KAKARIKO_VILLAGE &&
                    CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST) &&
                    CHECK_QUEST_ITEM(QUEST_MEDALLION_FIRE) &&
                    CHECK_QUEST_ITEM(QUEST_MEDALLION_WATER);
            break;
        case GI_VB_GIVE_ITEM_MASTER_SWORD:
            if (RAND_GET_OPTION(RSK_SHUFFLE_MASTER_SWORD)) {
                *should = false;
            } else {
                *should = true;
                Rando::Context::GetInstance()->GetItemLocation(RC_TOT_MASTER_SWORD)->MarkAsObtained();
            }
            break;
        case GI_VB_ITEM00_DESPAWN: {
            EnItem00* item00 = static_cast<EnItem00*>(optionalArg);
            if (item00->actor.params == ITEM00_HEART_PIECE || item00->actor.params == ITEM00_SMALL_KEY) {
                RandomizerCheck rc = OTRGlobals::Instance->gRandomizer->GetCheckFromActor(item00->actor.id, gPlayState->sceneNum, item00->ogParams);
                if (rc != RC_UNKNOWN_CHECK) {
                    item00->actor.params = ITEM00_SOH_DUMMY;
                    item00->itemEntry = Rando::Context::GetInstance()->GetFinalGIEntry(rc, true, (GetItemID)Rando::StaticData::GetLocation(rc)->GetVanillaItem());
                    item00->actor.draw = (ActorFunc)EnItem00_DrawRandomizedItem;
                    *should = Rando::Context::GetInstance()->GetItemLocation(rc)->HasObtained();
                }
            } else if (item00->actor.params == ITEM00_SOH_GIVE_ITEM_ENTRY || item00->actor.params == ITEM00_SOH_GIVE_ITEM_ENTRY_GI) {
                GetItemEntry itemEntry = randomizerQueuedItemEntry;
                item00->itemEntry = itemEntry;
                item00->actor.draw = (ActorFunc)EnItem00_DrawRandomizedItem;
            }
            break;
        }
        case GI_VB_GIVE_ITEM_FROM_ITEM_00: {
            EnItem00* item00 = static_cast<EnItem00*>(optionalArg);
            if (item00->actor.params == ITEM00_SOH_DUMMY) {
                Flags_SetCollectible(gPlayState, item00->collectibleFlag);
                Actor_Kill(&item00->actor);
                *should = false;
            } else if (item00->actor.params == ITEM00_SOH_GIVE_ITEM_ENTRY) {
                Audio_PlaySoundGeneral(NA_SE_SY_GET_ITEM, &D_801333D4, 4, &D_801333E0, &D_801333E0, &D_801333E8);
                if (item00->itemEntry.modIndex == MOD_NONE) {
                    if (item00->itemEntry.getItemId == GI_SWORD_BGS) {
                        gSaveContext.bgsFlag = true;
                    }
                    Item_Give(gPlayState, item00->itemEntry.itemId);
                } else if (item00->itemEntry.modIndex == MOD_RANDOMIZER) {
                    if (item00->itemEntry.getItemId == RG_ICE_TRAP) {
                        gSaveContext.pendingIceTrapCount++;
                    } else {
                        Randomizer_Item_Give(gPlayState, item00->itemEntry);
                    }
                }
                // EnItem00_SetupAction(item00, func_8001E5C8);
                // *should = false;
            } else if (item00->actor.params == ITEM00_SOH_GIVE_ITEM_ENTRY_GI) {
                if (!Actor_HasParent(&item00->actor, gPlayState)) {
                    GiveItemEntryFromActorWithFixedRange(&item00->actor, gPlayState, item00->itemEntry);
                }
                EnItem00_SetupAction(item00, func_8001E5C8);
                *should = false;
            }
            break;
        }
        case GI_VB_GIVE_ITEM_FROM_COW: {
            if (!RAND_GET_OPTION(RSK_SHUFFLE_COWS)) {
                break;
            }
            EnCow* enCow = static_cast<EnCow*>(optionalArg);
            CowIdentity cowIdentity = OTRGlobals::Instance->gRandomizer->IdentifyCow(gPlayState->sceneNum, enCow->actor.world.pos.x, enCow->actor.world.pos.z);
            // Has this cow already rewarded an item?
            if (Flags_GetRandomizerInf(cowIdentity.randomizerInf)) {
                break;
            }
            Flags_SetRandomizerInf(cowIdentity.randomizerInf);
            // setting the ocarina mode here prevents intermittent issues
            // with the item get not triggering until walking away
            gPlayState->msgCtx.ocarinaMode = OCARINA_MODE_00;
            *should = false;
            break;
        }
        case GI_VB_DESPAWN_HORSE_RACE_COW: {
            if (!RAND_GET_OPTION(RSK_SHUFFLE_COWS)) {
                break;
            }
            EnCow* enCow = static_cast<EnCow*>(optionalArg);
            // If this is a cow we have to move, then move it now.
            EnCow_MoveForRandomizer(enCow, gPlayState);
            break;
        }
        case GI_VB_BUSINESS_SCRUB_DESPAWN: {
            EnShopnuts* enShopnuts = static_cast<EnShopnuts*>(optionalArg);
            s16 respawnData = gSaveContext.respawn[RESPAWN_MODE_RETURN].data & ((1 << 8) - 1);
            ScrubIdentity scrubIdentity = OTRGlobals::Instance->gRandomizer->IdentifyScrub(gPlayState->sceneNum, enShopnuts->actor.params, respawnData);

            if (scrubIdentity.isShuffled) {
                *should = Flags_GetRandomizerInf(scrubIdentity.randomizerInf);
            }
            break;
        }
        case GI_VB_GIVE_ITEM_FROM_BUSINESS_SCRUB: {
            EnDns* enDns = static_cast<EnDns*>(optionalArg);
            *should = !enDns->sohScrubIdentity.isShuffled;
            break;
        }
        case GI_VB_GIVE_ITEM_SKULL_TOKEN:
        case GI_VB_GIVE_ITEM_FROM_BLUE_WARP:
        case GI_VB_GIVE_ITEM_FAIRY_OCARINA:
        case GI_VB_GIVE_ITEM_WEIRD_EGG:
        case GI_VB_GIVE_ITEM_LIGHT_ARROW:
        case GI_VB_GIVE_ITEM_STRENGTH_1:
        case GI_VB_GIVE_ITEM_ZELDAS_LETTER:
        case GI_VB_GIVE_ITEM_OCARINA_OF_TIME:
        case GI_VB_GIVE_ITEM_KOKIRI_EMERALD:
        case GI_VB_GIVE_ITEM_GORON_RUBY:
        case GI_VB_GIVE_ITEM_ZORA_SAPPHIRE:
        case GI_VB_GIVE_ITEM_LIGHT_MEDALLION:
        case GI_VB_GIVE_ITEM_FOREST_MEDALLION:
        case GI_VB_GIVE_ITEM_FIRE_MEDALLION:
        case GI_VB_GIVE_ITEM_WATER_MEDALLION:
        case GI_VB_GIVE_ITEM_SPIRIT_MEDALLION:
        case GI_VB_GIVE_ITEM_SHADOW_MEDALLION:
            *should = false;
            break;
    }
}

void RandomizerOnSceneInitHandler(int16_t sceneNum) {
    // LACs & Prelude checks
    static uint32_t updateHook = 0;

    if (updateHook) {
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(updateHook);
        updateHook = 0;
    }

    if (
        sceneNum != SCENE_TEMPLE_OF_TIME || 
        (
            Flags_GetEventChkInf(EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT) &&
            Flags_GetEventChkInf(EVENTCHKINF_RETURNED_TO_TEMPLE_OF_TIME_WITH_ALL_MEDALLIONS)
        )
    ) return;

    updateHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
        if (!Flags_GetEventChkInf(EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT) && LINK_IS_ADULT && CHECK_QUEST_ITEM(QUEST_MEDALLION_FOREST) && gPlayState->roomCtx.curRoom.num == 0) {
            Flags_SetEventChkInf(EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT);
        }

        if (!Flags_GetEventChkInf(EVENTCHKINF_RETURNED_TO_TEMPLE_OF_TIME_WITH_ALL_MEDALLIONS) && MeetsLACSRequirements()) {
            Flags_SetEventChkInf(EVENTCHKINF_RETURNED_TO_TEMPLE_OF_TIME_WITH_ALL_MEDALLIONS);
        }

        if (
            Flags_GetEventChkInf(EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT) &&
            Flags_GetEventChkInf(EVENTCHKINF_RETURNED_TO_TEMPLE_OF_TIME_WITH_ALL_MEDALLIONS)
        ) {
            GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(updateHook);
        }
    });
}

void EnSi_DrawRandomizedItem(EnSi* enSi, PlayState* play) {
    func_8002ED80(&enSi->actor, play, 0);
    func_8002EBCC(&enSi->actor, play, 0);
    EnItem00_CustomItemsParticles(&enSi->actor, play, enSi->sohGetItemEntry);
    GetItemEntry_Draw(play, enSi->sohGetItemEntry);
}

u32 EnDns_RandomizerPurchaseableCheck(EnDns* enDns) {
    if (Flags_GetRandomizerInf(enDns->sohScrubIdentity.randomizerInf)) {
        return 3; // Can't get this now
    }
    if (gSaveContext.rupees < enDns->dnsItemEntry->itemPrice) {
        return 0; // Not enough rupees
    }
    return 4;
}

void EnDns_RandomizerPurchase(EnDns* enDns) {
    Rupees_ChangeBy(-enDns->dnsItemEntry->itemPrice);
    Flags_SetRandomizerInf(enDns->sohScrubIdentity.randomizerInf);
}

void RandomizerOnActorInitHandler(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id == ACTOR_EN_SI) {
        RandomizerCheck rc = OTRGlobals::Instance->gRandomizer->GetCheckFromActor(actor->id, gPlayState->sceneNum, actor->params);
        if (rc != RC_UNKNOWN_CHECK) {
            EnSi* enSi = static_cast<EnSi*>(actorRef);
            enSi->sohGetItemEntry = Rando::Context::GetInstance()->GetFinalGIEntry(rc, true, (GetItemID)Rando::StaticData::GetLocation(rc)->GetVanillaItem());
            actor->draw = (ActorFunc)EnSi_DrawRandomizedItem;
        }
    }

    if (actor->id == ACTOR_EN_DNS) {
        EnDns* enDns = static_cast<EnDns*>(actorRef);
        s16 respawnData = gSaveContext.respawn[RESPAWN_MODE_RETURN].data & ((1 << 8) - 1);
        enDns->sohScrubIdentity = OTRGlobals::Instance->gRandomizer->IdentifyScrub(gPlayState->sceneNum, enDns->actor.params, respawnData);

        if (enDns->sohScrubIdentity.isShuffled) {
            // DNS uses pointers so we're creating our own entry instead of modifying the original
            enDns->sohDnsItemEntry = {
                enDns->dnsItemEntry->itemPrice,
                1,
                enDns->sohScrubIdentity.getItemId,
                EnDns_RandomizerPurchaseableCheck,
                EnDns_RandomizerPurchase,
            };
            enDns->dnsItemEntry = &enDns->sohDnsItemEntry;

            if (enDns->sohScrubIdentity.itemPrice != -1) {
                enDns->dnsItemEntry->itemPrice = enDns->sohScrubIdentity.itemPrice;
            }

            enDns->actor.textId = TEXT_SCRUB_RANDOM;

            static uint32_t enDnsUpdateHook = 0;
            static uint32_t enDnsKillHook = 0;
            if (!enDnsUpdateHook) {
                enDnsUpdateHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorUpdate>([](void* innerActorRef) {
                    Actor* innerActor = static_cast<Actor*>(innerActorRef);
                    if (innerActor->id == ACTOR_EN_DNS) {
                        EnDns* innerEnDns = static_cast<EnDns*>(innerActorRef);
                        if (innerEnDns->sohScrubIdentity.isShuffled) {
                            innerActor->textId = TEXT_SCRUB_RANDOM;
                        }
                    }
                });
                enDnsKillHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneInit>([](int16_t sceneNum) {
                    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnActorUpdate>(enDnsUpdateHook);
                    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneInit>(enDnsKillHook);
                    enDnsUpdateHook = 0;
                    enDnsKillHook = 0;
                });
            }
        }
    }
}

void RandomizerRegisterHooks() {
    static uint32_t onFlagSetHook = 0;
    static uint32_t onSceneFlagSetHook = 0;
    static uint32_t onPlayerUpdateForRCQueueHook = 0;
    static uint32_t onPlayerUpdateForItemQueueHook = 0;
    static uint32_t onItemReceiveHook = 0;
    static uint32_t onVanillaBehaviorHook = 0;
    static uint32_t onSceneInitHook = 0;
    static uint32_t onActorInitHook = 0;

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnLoadGame>([](int32_t fileNum) {
        randomizerQueuedChecks = std::queue<RandomizerCheck>();
        randomizerQueuedCheck = RC_UNKNOWN_CHECK;
        randomizerQueuedItemEntry = GET_ITEM_NONE;

        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnFlagSet>(onFlagSetHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneFlagSet>(onSceneFlagSetHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(onPlayerUpdateForRCQueueHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnPlayerUpdate>(onPlayerUpdateForItemQueueHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnItemReceive>(onItemReceiveHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnVanillaBehavior>(onVanillaBehaviorHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnSceneInit>(onSceneInitHook);
        GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnActorInit>(onActorInitHook);

        onFlagSetHook = 0;
        onSceneFlagSetHook = 0;
        onPlayerUpdateForRCQueueHook = 0;
        onPlayerUpdateForItemQueueHook = 0;
        onItemReceiveHook = 0;
        onVanillaBehaviorHook = 0;
        onSceneInitHook = 0;
        onActorInitHook = 0;

        if (!IS_RANDO) return;

        onFlagSetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnFlagSet>(RandomizerOnFlagSetHandler);
        onSceneFlagSetHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneFlagSet>(RandomizerOnSceneFlagSetHandler);
        onPlayerUpdateForRCQueueHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>(RandomizerOnPlayerUpdateForRCQueueHandler);
        onPlayerUpdateForItemQueueHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>(RandomizerOnPlayerUpdateForItemQueueHandler);
        onItemReceiveHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnItemReceive>(RandomizerOnItemReceiveHandler);
        onVanillaBehaviorHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnVanillaBehavior>(RandomizerOnVanillaBehaviorHandler);
        onSceneInitHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneInit>(RandomizerOnSceneInitHandler);
        onActorInitHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorInit>(RandomizerOnActorInitHandler);
    });
}
