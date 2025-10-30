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

    // Test Quest Add
    // RogueLike::Quests::AddQuestById(RL_QUEST_HF_STALFOS);

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

            RogueLike::XP::SpawnXPGroup(GET_PLAYER(gPlayState)->actor.world.pos, 10);
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
            RogueLike::Quests::AddQuestById(RL_QUEST_ZD_POTTERY);
        } else {
            messageEntry = CustomMessage(
                "The sound, wasn't that exhilarating? There may be a few more pots if you fancy another go." +
                endOfMessage);
            RogueLike::Quests::CompleteQuestById(RL_QUEST_ZD_POTTERY);
        }

        messageEntry.AutoFormat();
        messageEntry.LoadIntoFont();
        *loadFromMessageTable = false;
    });
}

static RegisterShipInitFunc initFunc(InitRogueLikeQuests, {});
static RegisterShipInitFunc initFunc2(OnLoadGame, { "IS_ROGUELIKE" });