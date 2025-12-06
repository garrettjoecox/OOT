#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/ActorDB.h"
#include "soh/Enhancements/custom-message/CustomMessageManager.h"
#include "soh/Notification/Notification.h"

extern "C" {
#include "variables.h"
#include <macros.h>
#include <functions.h>

#include "overlays/actors/ovl_Bg_Mjin/z_bg_mjin.h"
#include "overlays/actors/ovl_En_Vm/z_en_vm.h"

extern PlayState* gPlayState;
s32 Object_Spawn(ObjectContext* objectCtx, s16 objectId);
}

// clang-format off
std::vector<RogueLikeQuestObject> rogueLikeQuestList = {
    { RL_QUEST_HF_TRIAL_A, "Ganon's Fury I", "Watch out!", RL_QUEST_ACTIVE, 0, 1 },
    { RL_QUEST_HF_TRIAL_B, "Ganon's Fury II", "Get to Gerudo Valley\nbefore time runs out!", RL_QUEST_ACTIVE, 0, 1 },
    { RL_QUEST_KF_HOPOFFAITH, "Hop of Faith", "Sidehop from the fence\nabove the waterfall and land\non the middle platform.", RL_QUEST_ACTIVE, 0, 1},
    { RL_QUEST_KF_STRONGMAN, "Toe Crushers", "Mido likes rock, show them\nthat we don't!", RL_QUEST_ACTIVE, 0, 11 },
    { RL_QUEST_KV_POTHUNT, "The Pot Thickens", "A magical pot with extra lives?\nFind out how many!", RL_QUEST_ACTIVE, 0, 4 },
    { RL_QUEST_KV_STALFOS, "Stal-Not-So-Child", "The Stalchild in Hyrule Field have\ngotten bigger, take them out!", RL_QUEST_ACTIVE, 0, 5 },
    { RL_QUEST_ZD_POTTERY, "A Smashing View", "Toss a pot off the edge\nof the waterfall.", RL_QUEST_ACTIVE, 0, 1 },
};

std::vector<Vec3f> potHuntLocations = {
    { 150.378f, 300.0f, 1166.648f },
    { 6.151f, 755.0f, -91.802f },
    { 1760.740f, 542.62f, 534.236f },
    { -381.964f, 240.0f, 1597.884f },
};

const std::vector<std::pair<Vec3f, int16_t>> trialAActorSpawnList = {
    { { 563.838f, -0, 3059.409f }, -27275 },
    { { 678.031f, -0, 2563.164f }, -10891 },
    { { 185.132f, -0, 2404.207f }, -27275 },
    { { 36.108f, -0, 2925.440f }, -10891 },
    { { 335.571f, 20.0f, 2677.854f }, 0 },
};
// clang-format on

Actor* trialActorSlot = NULL;
extern std::vector<RogueLikeQuestObject> activeQuests;
static std::vector<Vec3f> potHuntAvailability;
static std::vector<Actor*> currentTrialActorList;
static bool potHuntActorSpawned = false;
static bool sendConditionMessage = true;

bool CheckActiveQuestById(u8 questId) {
    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            return true;
        }
    }
    return false;
}

bool CheckQuestGoalCompleteById(u8 questId) {
    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            return (quest.questProgress == quest.questGoal);
        }
    }
    return false;
}

bool CheckQuestCompletedById(u8 questId) {
    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            return (quest.questStatus);
        }
    }
    return false;
}

void SendQuestConditionMessage(u8 questId) {
    if (!sendConditionMessage) {
        return;
    }

    std::string message = "";
    ImVec4 color = ImVec4(1, 1, 1, 1);

    switch (questId) {
        case RL_QUEST_KV_POTHUNT:
            message = "A Magical Pot has appeared nearby.";
            color = ImVec4(0, 0.25f, 0.75f, 1);
            break;
        case RL_QUEST_HF_TRIAL_A:
            message = "Come back when you have a sword...";
            color = ImVec4(1, 0, 0, 1);
            break;
        case RL_QUEST_HF_TRIAL_B:
            message = "Come back when you're faster...";
            color = ImVec4(1, 0, 0, 1);
            break;
        default:
            return;
    }
    Notification::Emit({
        .message = message,
        .messageColor = color,
    });
    sendConditionMessage = false;
}

void RogueLike::Quests::CompleteQuestById(u8 questId) {
    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            quest.questStatus = RL_QUEST_COMPLETE;
            break;
        }
    }
}

void RogueLike::Quests::RemoveQuestById(u8 questId) {
    int index = -1;
    for (int i = 0; i < activeQuests.size(); i++) {
        if (activeQuests[i].questId == questId) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        activeQuests.erase(activeQuests.begin() + index);
    }
}

void RogueLike::Quests::AddQuestById(u8 questId) {
    if (CheckActiveQuestById(questId)) {
        return;
    }

    activeQuests.push_back(rogueLikeQuestList[questId]);
}

u16 GetQuestProgress(u8 questId) {
    if (!CheckActiveQuestById(questId)) {
        return 0;
    }

    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            return quest.questProgress;
        }
    }

    return 0;
}

u16 GetQuestGoal(u8 questId) {
    if (!CheckActiveQuestById(questId)) {
        return 0;
    }

    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            return quest.questGoal;
        }
    }

    return 0;
}

u16 DetermineInitialQuestProgress(u8 questId, int16_t progressActor) {
    ActorListEntry actorList = gPlayState->actorCtx.actorLists[ACTORCAT_PROP];
    u16 initialProgress = GetQuestGoal(questId);
    if (questId == RL_QUEST_KF_STRONGMAN) {
        initialProgress++;
    }

    Actor* currentActor = actorList.head;
    while (currentActor != nullptr) {
        if (currentActor->id == progressActor) {
            initialProgress--;
        }
        currentActor = currentActor->next;
    }

    return initialProgress;
}

void RogueLike::Quests::UpdateQuestProgress(u8 questId) {
    if (!CheckActiveQuestById(questId)) {
        return;
    }

    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            quest.questProgress++;
            break;
        }
    }
}

void RogueLike::Quests::SetQuestProgress(u8 questId, u16 progress) {
    if (!CheckActiveQuestById(questId)) {
        return;
    }

    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            quest.questProgress = progress;
            break;
        }
    }
}

void RogueLike::Quests::ResetQuestProgress(u8 questId) {
    if (!CheckActiveQuestById(questId)) {
        return;
    }

    if (CheckQuestGoalCompleteById(questId)) {
        return;
    }

    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            if (questId == RL_QUEST_KV_POTHUNT) {
                potHuntAvailability.clear();
            }
            quest.questProgress = 0;
            break;
        }
    }
}

// StartQuest() - Used for Quest Specific Functions.
void StartQuest(u8 questId) {
    uint32_t index = 0;
    switch (questId) {
        case RL_QUEST_HF_TRIAL_A:
            if (!CheckQuestGoalCompleteById(RL_QUEST_HF_TRIAL_A)) {
                GameInteractor::RawAction::SetWeatherStorm(true);
                for (auto& slot : trialAActorSpawnList) {
                    if (slot.first.y != 20.0f) {
                        trialActorSlot =
                            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_BG_HIDAN_FWBIG, slot.first.x,
                                        slot.first.y, slot.first.z, 0, slot.second, 0, 0, false);
                        currentTrialActorList.push_back(trialActorSlot);
                    } else {
                        EnVm* beamosActor =
                            (EnVm*)Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_VM, slot.first.x,
                                               slot.first.y, slot.first.z, 0, slot.second, 0, 0, false);
                        beamosActor->beamSightRange = 400.0f;
                        currentTrialActorList.push_back(&beamosActor->actor);
                    }
                    index++;
                }
                Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_ZF, 255.359f, -0, 3134.437f, 0, 0, 0, -2,
                            false);
            } else {
                RogueLike::Quests::CompleteQuestById(RL_QUEST_HF_TRIAL_A);
                uint32_t reward = RogueLike::XP::ConvertLevelToXP(RogueLike::XP::GetCurrentLevel() + 1);
                RogueLike::XP::GrantXP(reward);
                for (auto& kill : currentTrialActorList) {
                    Actor_Kill(kill);
                    kill = NULL;
                }
                currentTrialActorList.clear();
                GameInteractor::RawAction::SetWeatherStorm(false);
            }
            break;
        case RL_QUEST_HF_TRIAL_B:
            if (!CheckQuestGoalCompleteById(RL_QUEST_HF_TRIAL_B)) {
                GameInteractor::RawAction::SetWeatherStorm(true);
                gSaveContext.timerState = 6;
                gSaveContext.timerSeconds = 70;
            } else {
                RogueLike::Quests::CompleteQuestById(RL_QUEST_HF_TRIAL_B);
                uint32_t reward = RogueLike::XP::ConvertLevelToXP(RogueLike::XP::GetCurrentLevel() + 1);
                gSaveContext.timerState = 0;
                gSaveContext.timerSeconds = 0;
                GameInteractor::RawAction::SetWeatherStorm(false);
            }
            break;
        case RL_QUEST_KV_POTHUNT:
            if (!CheckQuestGoalCompleteById(RL_QUEST_KV_POTHUNT)) {
                if (potHuntAvailability.size() == 0) {
                    potHuntAvailability = potHuntLocations;
                }
                u8 potRoll = rand() % potHuntAvailability.size();
                Vec3f spawnPoint = potHuntAvailability[potRoll];
                Actor* potActor = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_OBJ_TSUBO, spawnPoint.x,
                                              spawnPoint.y, spawnPoint.z, 0, 0, 0, 256, false);
                Actor_SetColorFilter(potActor, 0x1000, 150, 0, 1000);
                potHuntAvailability.erase(potHuntAvailability.begin() + potRoll);
                sendConditionMessage = true;
                SendQuestConditionMessage(RL_QUEST_KV_POTHUNT);
            }
            break;
        case RL_QUEST_KV_STALFOS:
            if (!CheckQuestGoalCompleteById(RL_QUEST_KV_STALFOS)) {
                float centerX = 2475.3f;
                float centerZ = 496.3f;
                float radius = 100.0f;

                for (int i = 0; i < GetQuestGoal(RL_QUEST_KV_STALFOS); i++) {
                    float angle = i * (2 * M_PI / 5);
                    float spawnX = centerX + radius * cosf(angle);
                    float spawnZ = centerZ + radius * sinf(angle);

                    if (ActorDB::Instance->RetrieveEntry(ACTOR_EN_TEST).entry.valid) {
                        Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_TEST, spawnX, -4.7f, spawnZ, 0, 0, 0, 1,
                                    0);
                    }
                }
            }
            break;
        default:
            break;
    }
}

RogueLikeQuest FindTrialByLocation(Actor* trialActor) {
    switch (gPlayState->sceneNum) {
        case SCENE_HYRULE_FIELD:
            if (trialActor->world.pos.x == 335.571f && trialActor->world.pos.z == 2677.854f) {
                if (LINK_IS_ADULT && ((EQUIP_FLAG_SWORD_MASTER & gSaveContext.inventory.equipment) ||
                                      (EQUIP_FLAG_SWORD_BGS & gSaveContext.inventory.equipment))) {
                    return RL_QUEST_HF_TRIAL_A;
                } else {
                    SendQuestConditionMessage(RL_QUEST_HF_TRIAL_A);
                }
            }
            if (trialActor->world.pos.x == 1490.550f && trialActor->world.pos.z == 8760.643f) {
                if (LINK_IS_ADULT) {
                    return RL_QUEST_HF_TRIAL_B;
                }
            }
            break;
        default:
            break;
    }

    return RL_QUEST_ID_MAX;
}

static void InitRogueLikeQuests() {
    activeQuests.clear();
    currentTrialActorList.clear();
}

static void OnLoadGame() {
    activeQuests.clear();
    for (auto& load : gSaveContext.ship.quest.data.rogueLike.quests) {
        if (load.questDescription != NULL) {
            activeQuests.push_back(load);
        }
    }

    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, []() {
        Player* player = GET_PLAYER(gPlayState);
        RogueLikeQuest questId = RL_QUEST_ID_MAX;
        static bool hopOfFaithStart = false;
        static bool trialTimerInit = false;
        static uint32_t trialTimer = 0;

        if (trialTimerInit == false) {
            trialTimer = gPlayState->gameplayFrames;
            trialTimerInit = true;
        }

        if (CheckActiveQuestById(RL_QUEST_HF_TRIAL_B) && !CheckQuestGoalCompleteById(RL_QUEST_HF_TRIAL_B)) {
            if (gSaveContext.timerState == 6) {
                if (gSaveContext.timerSeconds > 0) {
                    if (trialTimer <= gPlayState->gameplayFrames - 20) {
                        gSaveContext.timerSeconds--;
                        trialTimer = gPlayState->gameplayFrames;
                    }
                } else if (gSaveContext.timerSeconds <= 0) {
                    gSaveContext.health = 4;
                    gSaveContext.timerState = 0;
                    gSaveContext.timerSeconds = 0;
                    RogueLike::Quests::RemoveQuestById(RL_QUEST_HF_TRIAL_B);
                    sendConditionMessage = true;
                    SendQuestConditionMessage(RL_QUEST_HF_TRIAL_B);
                }
            }
        }

        if (CheckActiveQuestById(RL_QUEST_KF_HOPOFFAITH) && !CheckQuestGoalCompleteById(RL_QUEST_KF_HOPOFFAITH)) {
            bool isHopping = (player->stateFlags2 & PLAYER_STATE2_HOPPING);
            if (!hopOfFaithStart && isHopping && player->actor.world.pos.y >= 360.0f) {
                hopOfFaithStart = true;
            }
            if (hopOfFaithStart && !isHopping) {
                hopOfFaithStart = false;
                if ((player->actor.world.pos.x >= 318.0f && player->actor.world.pos.x <= 418.0f) &&
                    (player->actor.world.pos.z >= -227.6f && player->actor.world.pos.z <= -126.5f)) {
                    RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KF_HOPOFFAITH);
                }
            }
        }
        if (gPlayState->sceneNum == SCENE_HYRULE_FIELD) {
            Actor* trialActor =
                Actor_FindNearby(gPlayState, &GET_PLAYER(gPlayState)->actor, ACTOR_BG_MJIN, ACTORCAT_BG, 45.0f);
            if (trialActor != NULL) {
                questId = FindTrialByLocation(trialActor);
                if (questId != RL_QUEST_ID_MAX) {
                    if (!CheckActiveQuestById(questId)) {
                        RogueLike::Quests::AddQuestById(questId);
                        StartQuest(questId);
                    }
                }
            }
        }
    });

    COND_HOOK(OnSceneInit, IS_ROGUELIKE, [](u16 sceneNum) {
        if (CheckActiveQuestById(RL_QUEST_HF_TRIAL_B) && gSaveContext.timerState == 6 &&
            gPlayState->sceneNum == SCENE_GERUDO_VALLEY) {
            if (gSaveContext.timerSeconds > 0) {
                RogueLike::Quests::UpdateQuestProgress(RL_QUEST_HF_TRIAL_B);
            }
        }
        for (auto& quest : activeQuests) {
            RogueLike::Quests::ResetQuestProgress(quest.questId);
        }
        sendConditionMessage = true;
    });

    COND_HOOK(OnRoomInit, IS_ROGUELIKE, [](u16 roomNum) {
        if (gPlayState->sceneNum == SCENE_KOKIRI_FOREST) {
            if (CheckActiveQuestById(RL_QUEST_KF_STRONGMAN)) {
                if (!CheckQuestCompletedById(RL_QUEST_KF_STRONGMAN)) {
                    RogueLike::Quests::ResetQuestProgress(RL_QUEST_KF_STRONGMAN);
                }
            }
        }
    });

    COND_HOOK(OnSceneSpawnActors, IS_ROGUELIKE, []() {
        if (gPlayState->sceneNum == SCENE_HYRULE_FIELD) {
            if (CheckActiveQuestById(RL_QUEST_KV_STALFOS)) {
                StartQuest(RL_QUEST_KV_STALFOS);
            }
            Object_Spawn(&gPlayState->objectCtx, OBJECT_MJIN);
            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_BG_MJIN, 335.571f, -0.0f, 2677.854f, 0, 0, 0, 1,
                        false);
            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_BG_MJIN, 1490.550f, -135.0f, 8760.643f, 0, 0, 0, 1,
                        false);
        }
    });

    COND_HOOK(OnActorKill, IS_ROGUELIKE, [](void* actor) {
        Actor* refActor = (Actor*)actor;

        switch (refActor->id) {
            case ACTOR_EN_TEST:
                if (CheckActiveQuestById(RL_QUEST_KV_STALFOS) && gPlayState->sceneNum == SCENE_HYRULE_FIELD) {
                    if (!CheckQuestGoalCompleteById(RL_QUEST_KV_STALFOS)) {
                        RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KV_STALFOS);
                    }
                }
                break;
            case ACTOR_OBJ_TSUBO:
                if (gPlayState->sceneNum == SCENE_ZORAS_DOMAIN) {
                    if (CheckActiveQuestById(RL_QUEST_ZD_POTTERY)) {
                        if (!(CheckQuestGoalCompleteById(RL_QUEST_ZD_POTTERY) &&
                              CheckQuestCompletedById(RL_QUEST_ZD_POTTERY))) {
                            if (GET_PLAYER(gPlayState)->actor.world.pos.y >= 830.0f &&
                                refActor->world.pos.y <= 800.0f) {
                                RogueLike::Quests::UpdateQuestProgress(RL_QUEST_ZD_POTTERY);
                            }
                        }
                    }
                } else if (gPlayState->sceneNum == SCENE_KAKARIKO_VILLAGE) {
                    if (CheckActiveQuestById(RL_QUEST_KV_POTHUNT) && refActor->params == 256) {
                        if (!(CheckQuestGoalCompleteById(RL_QUEST_KV_POTHUNT) &&
                              CheckQuestCompletedById(RL_QUEST_KV_POTHUNT))) {
                            RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KV_POTHUNT);
                            StartQuest(RL_QUEST_KV_POTHUNT);
                        }
                    }
                }
                break;
            case ACTOR_EN_ISHI:
                if (refActor->world.pos.x == refActor->home.pos.x && refActor->world.pos.z == refActor->home.pos.z) {
                    return;
                }
                if (CheckActiveQuestById(RL_QUEST_KF_STRONGMAN) && gPlayState->sceneNum == SCENE_KOKIRI_FOREST &&
                    gPlayState->roomCtx.curRoom.num == 0) {
                    if (!CheckQuestGoalCompleteById(RL_QUEST_KF_STRONGMAN)) {
                        RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KF_STRONGMAN);
                    }
                }
                break;
            case ACTOR_EN_ZF:
                if (gPlayState->sceneNum == SCENE_HYRULE_FIELD) {
                    if (CheckActiveQuestById(RL_QUEST_HF_TRIAL_A)) {
                        if (!CheckQuestGoalCompleteById(RL_QUEST_HF_TRIAL_A)) {
                            RogueLike::Quests::UpdateQuestProgress(RL_QUEST_HF_TRIAL_A);
                            StartQuest(RL_QUEST_HF_TRIAL_A);
                        }
                    }
                }
                break;
            default:
                break;
        }
    });

    // RL_QUEST_KV_STALFOS
    COND_ID_HOOK(OnOpenText, 0x503e, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 4);
        auto messageEntry = CustomMessage("Stalfos have been attacking our Cucco's, please help us!" + endOfMessage);
        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    COND_ID_HOOK(OnOpenText, 0x5042, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        if (CheckQuestGoalCompleteById(RL_QUEST_KV_STALFOS) && !CheckQuestCompletedById(RL_QUEST_KV_STALFOS)) {
            auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
            std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
            auto messageEntry = CustomMessage("Thank you for saving our cucco's!" + endOfMessage);
            messageEntry.AutoFormat();
            messageEntry.LoadIntoFont();

            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 20);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_KV_STALFOS);

            *loadFromMessageTable = false;
        }
    });

    // RL_QUEST_ZD_POTTERY
    COND_ID_HOOK(OnOpenText, 0x4006, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("Have you ever heard the sound of ceramic shattering against the water? You "
                                          "should give it a try, it's beautiful!" +
                                          endOfMessage);
        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();

        RogueLike::Quests::AddQuestById(RL_QUEST_ZD_POTTERY);

        *loadFromMessageTable = false;
    });

    COND_ID_HOOK(OnOpenText, 0x4007, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckQuestGoalCompleteById(RL_QUEST_ZD_POTTERY)) {
            messageEntry = CustomMessage(
                "Need a tip? Take one of the Pots outside of the Shop and toss it over the top of the waterfall." +
                endOfMessage);
        } else {
            messageEntry = CustomMessage(
                "The sound, wasn't that exhilarating? There may be a few more pots if you fancy another go." +
                endOfMessage);
            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_ZD_POTTERY);
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    // RL_QUEST_KF_STRONGMAN
    COND_ID_HOOK(OnOpenText, 0x1004, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckQuestGoalCompleteById(RL_QUEST_KF_STRONGMAN)) {
            messageEntry = CustomMessage(
                "Stupid Mido likes these stupid rocks! Don't just stand there, help me smash them!" + endOfMessage);
            if (!CheckActiveQuestById(RL_QUEST_KF_STRONGMAN)) {
                RogueLike::Quests::AddQuestById(RL_QUEST_KF_STRONGMAN);
                RogueLike::Quests::SetQuestProgress(
                    RL_QUEST_KF_STRONGMAN, DetermineInitialQuestProgress(RL_QUEST_KF_STRONGMAN, ACTOR_EN_ISHI));
            }
        } else {
            messageEntry = CustomMessage("Thanks for being one of the good guys! Oh, this one? Don't worry, I'll have "
                                         "it smashed by your 17th birthday." +
                                         endOfMessage);
            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_KF_STRONGMAN);
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    // RL_QUEST_KF_HOPOFFAITH
    COND_ID_HOOK(OnOpenText, 0x10d7, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 4);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckActiveQuestById(RL_QUEST_KF_HOPOFFAITH)) {
            messageEntry =
                CustomMessage("Wow, you came all the way to see me? Not afraid of heights I see." + endOfMessage);
        } else {
            Message_ContinueTextbox(gPlayState, 0x10d8);
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    COND_ID_HOOK(OnOpenText, 0x10d8, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckActiveQuestById(RL_QUEST_KF_HOPOFFAITH)) {
            messageEntry =
                CustomMessage("If we're going to continue meeting like this, let's see what you got!" + endOfMessage);
            RogueLike::Quests::AddQuestById(RL_QUEST_KF_HOPOFFAITH);
        } else {
            if (!CheckQuestGoalCompleteById(RL_QUEST_KF_HOPOFFAITH)) {
                messageEntry = CustomMessage("Can't read the Quest List, huh. See that fence above the waterfall? "
                                             "Sidehop off of it and land on the middle platform below." +
                                             endOfMessage);
            } else {
                messageEntry =
                    CustomMessage("Hey, nice distance! They say you can unload doors doing that." + endOfMessage);
                if (!CheckQuestCompletedById(RL_QUEST_KF_HOPOFFAITH)) {
                    RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
                    RogueLike::Quests::CompleteQuestById(RL_QUEST_KF_HOPOFFAITH);
                }
            }
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    // RL_QUEST_KV_POTHUNT
    COND_ID_HOOK(OnOpenText, 0x5036, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckActiveQuestById(RL_QUEST_KV_POTHUNT)) {
            messageEntry = CustomMessage("I've noticed you have a knack for smashing things. I developed a special Pot "
                                         "that could use testing, it's hidden around here somewhere." +
                                         endOfMessage);
            RogueLike::Quests::AddQuestById(RL_QUEST_KV_POTHUNT);
            StartQuest(RL_QUEST_KV_POTHUNT);
        } else {
            if (!CheckQuestGoalCompleteById(RL_QUEST_KV_POTHUNT)) {
                messageEntry = CustomMessage("It's hidden around here somewhere, get hunting!" + endOfMessage);
            } else {
                if (!CheckQuestCompletedById(RL_QUEST_KV_POTHUNT)) {
                    messageEntry =
                        CustomMessage("Nicely done! It's not much but here's something for your help." + endOfMessage);
                    RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
                    RogueLike::Quests::CompleteQuestById(RL_QUEST_KV_POTHUNT);
                } else {
                    messageEntry = CustomMessage("Thanks for your help." + endOfMessage);
                }
            }
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });
}

static RegisterShipInitFunc initFunc(InitRogueLikeQuests, {});
static RegisterShipInitFunc initFunc2(OnLoadGame, { "IS_ROGUELIKE" });