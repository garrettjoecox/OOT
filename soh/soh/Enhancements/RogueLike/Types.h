#ifndef ROGUELIKE_TYPES_H
#define ROGUELIKE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RL_HEALTH,
    RL_ATTACK,
    RL_DEFENSE,
    RL_SPEED,
    RL_MAX,
} RoguelikeStats;

typedef enum {
    RL_QUEST_ACTIVE,
    RL_QUEST_COMPLETE,
} RogueLikeQuestStatus;

typedef enum {
    RL_QUEST_HF_TRIAL_A,
    RL_QUEST_HF_TRIAL_B,
    RL_QUEST_KF_HOPOFFAITH,
    RL_QUEST_KF_STRONGMAN,
    RL_QUEST_KV_POTHUNT,
    RL_QUEST_KV_STALFOS,
    RL_QUEST_ZD_POTTERY,
    RL_QUEST_ID_MAX,
} RogueLikeQuest;

typedef struct {
    u8 questId;
    const char* questName;
    const char* questDescription;
    u8 questStatus;
    u16 questProgress;
    u16 questGoal;
} RogueLikeQuestObject;

#ifdef __cplusplus
}
#endif

#endif // ROGUELIKE_TYPES_H
