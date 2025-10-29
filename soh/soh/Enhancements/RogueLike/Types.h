#ifndef ROGUELIKE_TYPES_H
#define ROGUELIKE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RL_ATTACK,
    RL_DEFENSE,
    RL_SPEED,
    RL_MAX,
} RoguelikeStats;

typedef enum {
    RL_QUEST_KILL,
    RL_QUEST_MAX,
} RogueLikeQuestTypes;

typedef enum {
    RL_QUEST_HF_STALFOS,
    RL_QUEST_ID_MAX,
} RogueLikeQuest;

typedef struct {
    u8 questId;
    u8 questType;
    const char* questName;
    const char* questDescription;
    u16 questProgress;
    u16 questGoal;
} RogueLikeQuestObject;

#ifdef __cplusplus
}
#endif

#endif // ROGUELIKE_TYPES_H
