#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/ActorDB.h"
#include "soh/Enhancements/custom-message/CustomMessageManager.h"

extern "C" {
#include "variables.h"
#include <macros.h>
#include <functions.h>

extern PlayState* gPlayState;
}

// clang-format off
std::vector<RogueLikeQuestObject> rogueLikeQuestList = {
    { RL_QUEST_HF_STALFOS, RL_QUEST_KILL, "Stal-Not-So-Child", "The Stalchild in Hyrule Field have\ngotten bigger, take them out!", RL_QUEST_ACTIVE, 0, 5 },
    { RL_QUEST_KF_HOPOFFAITH, RL_QUEST_SIGHTSEEING, "Hop of Faith", "Sidehop from the fence\nabove the waterfall and land\non the middle platform.", RL_QUEST_ACTIVE, 0, 1},
    { RL_QUEST_KF_STRONGMAN, RL_QUEST_SIGHTSEEING, "Toe Crushers", "Mido likes rock, show them\nthat we don't!", RL_QUEST_ACTIVE, 0, 11 },
    { RL_QUEST_ZD_POTTERY, RL_QUEST_SIGHTSEEING, "A Smashing View", "Toss a pot off the edge\nof the waterfall.", RL_QUEST_ACTIVE, 0, 1 },
};
// clang-format on

extern std::vector<RogueLikeQuestObject> activeQuests;

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

void RogueLike::Quests::CompleteQuestById(u8 questId) {
    for (auto& quest : activeQuests) {
        if (quest.questId == questId) {
            quest.questStatus = RL_QUEST_COMPLETE;
            break;
        }
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
            quest.questProgress = 0;
            break;
        }
    }
}

static void InitRogueLikeQuests() {
    activeQuests.clear();
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
        static bool hopOfFaithStart = false;

        if (CheckActiveQuestById(RL_QUEST_KF_HOPOFFAITH) && !CheckQuestGoalCompleteById(RL_QUEST_KF_HOPOFFAITH)) {
            bool isHopping = (player->stateFlags2 & PLAYER_STATE2_HOPPING);
            if (!hopOfFaithStart && isHopping && player->actor.world.pos.y >= 360.0f) {
                hopOfFaithStart = true;
                SPDLOG_INFO("Hopping started");
            }
            if (hopOfFaithStart && !isHopping) {
                hopOfFaithStart = false;
                SPDLOG_INFO("Hopping ended");
                SPDLOG_INFO("Player X: {} | Z: {}", std::to_string(player->actor.world.pos.x).c_str(),
                            std::to_string(player->actor.world.pos.z).c_str());
                if ((player->actor.world.pos.x >= 318.0f && player->actor.world.pos.x <= 418.0f) &&
                    (player->actor.world.pos.z >= -227.6f && player->actor.world.pos.z <= -126.5f)) {
                    RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KF_HOPOFFAITH);
                }
            }
        }
    });

    COND_HOOK(OnSceneInit, IS_ROGUELIKE, [](u16 sceneNum) {
        for (auto& quest : activeQuests) {
            RogueLike::Quests::ResetQuestProgress(quest.questId);
        }
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
            if (CheckActiveQuestById(RL_QUEST_HF_STALFOS)) {
                if (!CheckQuestGoalCompleteById(RL_QUEST_HF_STALFOS)) {
                    float centerX = 2475.3f;
                    float centerZ = 496.3f;
                    float radius = 100.0f;

                    for (int i = GetQuestProgress(RL_QUEST_HF_STALFOS); i < GetQuestGoal(RL_QUEST_HF_STALFOS); i++) {
                        float angle = i * (2 * M_PI / 5);
                        float spawnX = centerX + radius * cosf(angle);
                        float spawnZ = centerZ + radius * sinf(angle);

                        if (ActorDB::Instance->RetrieveEntry(ACTOR_EN_TEST).entry.valid) {
                            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_TEST, spawnX, -4.7f, spawnZ, 0, 0,
                                        0, 1, 0);
                        }
                    }
                }
            }
        }
    });

    COND_HOOK(OnActorKill, IS_ROGUELIKE, [](void* actor) {
        Actor* refActor = (Actor*)actor;

        switch (refActor->id) {
            case ACTOR_EN_TEST:
                if (CheckActiveQuestById(RL_QUEST_HF_STALFOS) && gPlayState->sceneNum == SCENE_HYRULE_FIELD) {
                    if (!CheckQuestGoalCompleteById(RL_QUEST_HF_STALFOS)) {
                        RogueLike::Quests::UpdateQuestProgress(RL_QUEST_HF_STALFOS);
                    }
                }
                break;
            case ACTOR_OBJ_TSUBO:
                if (CheckActiveQuestById(RL_QUEST_ZD_POTTERY)) {
                    if (!(CheckQuestGoalCompleteById(RL_QUEST_ZD_POTTERY) &&
                          CheckQuestCompletedById(RL_QUEST_ZD_POTTERY))) {
                        if (gPlayState->sceneNum == SCENE_ZORAS_DOMAIN &&
                            GET_PLAYER(gPlayState)->actor.world.pos.y >= 830.0f && refActor->world.pos.y <= 800.0f) {
                            RogueLike::Quests::UpdateQuestProgress(RL_QUEST_ZD_POTTERY);
                        }
                    }
                }
                break;
            case ACTOR_EN_ISHI:
                if (refActor->world.pos.x == refActor->home.pos.x && refActor->world.pos.z == refActor->home.pos.z) {
                    return;
                }
                if (CheckActiveQuestById(RL_QUEST_KF_STRONGMAN) && gPlayState->sceneNum == SCENE_KOKIRI_FOREST && gPlayState->roomCtx.curRoom.num == 0) {
                    if (!CheckQuestGoalCompleteById(RL_QUEST_KF_STRONGMAN)) {
                        RogueLike::Quests::UpdateQuestProgress(RL_QUEST_KF_STRONGMAN);
                    }
                }
                break;
            default:
                break;
        }
    });

    COND_ID_HOOK(OnOpenText, 0x503e, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 4);
        auto messageEntry = CustomMessage("Stalfos have been attacking our Cucco's, please help us!" + endOfMessage);
        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    COND_ID_HOOK(OnOpenText, 0x5042, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        if (CheckQuestGoalCompleteById(RL_QUEST_HF_STALFOS) && !CheckQuestCompletedById(RL_QUEST_HF_STALFOS)) {
            auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
            std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
            auto messageEntry = CustomMessage("Thank you for saving our cucco's!" + endOfMessage);
            messageEntry.AutoFormat();
            messageEntry.LoadIntoFont();

            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 20);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_HF_STALFOS);

            *loadFromMessageTable = false;
        }
    });

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

    COND_ID_HOOK(OnOpenText, 0x1004, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 2);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckQuestGoalCompleteById(RL_QUEST_KF_STRONGMAN)) {
            messageEntry = CustomMessage(
                "Stupid Mido likes these stupid rocks! Don't just stand there, help me smash them!" +
                endOfMessage);
            if (!CheckActiveQuestById(RL_QUEST_KF_STRONGMAN)) {
                RogueLike::Quests::AddQuestById(RL_QUEST_KF_STRONGMAN);
                RogueLike::Quests::SetQuestProgress(RL_QUEST_KF_STRONGMAN, DetermineInitialQuestProgress(RL_QUEST_KF_STRONGMAN, ACTOR_EN_ISHI));
            }
        } else {
            messageEntry = CustomMessage(
                "Thanks for being one of the good guys! Oh, this one? Don't worry, I'll have it smashed by your 17th birthday." +
                endOfMessage);
            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_KF_STRONGMAN);
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });

    COND_ID_HOOK(OnOpenText, 0x10d7, IS_ROGUELIKE, [](u16* textId, bool* loadFromMessageTable) {
        auto oldEntry = CustomMessage::LoadVanillaMessageTableEntry(*textId);
        std::string endOfMessage = oldEntry.GetEnglish().substr(oldEntry.GetEnglish().size() - 4);
        auto messageEntry = CustomMessage("" + endOfMessage);

        if (!CheckActiveQuestById(RL_QUEST_KF_HOPOFFAITH)) {
            messageEntry = CustomMessage(
                "Wow, you came all the way to see me? Not afraid of heights I see." +
                endOfMessage);
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
                messageEntry = CustomMessage("Hey, nice distance! They say you can unload doors doing that." +
                                             endOfMessage);
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
}

static RegisterShipInitFunc initFunc(InitRogueLikeQuests, {});
static RegisterShipInitFunc initFunc2(OnLoadGame, { "IS_ROGUELIKE" });