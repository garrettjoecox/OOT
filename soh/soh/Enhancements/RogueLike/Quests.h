#ifndef ROGUELIKE_QUESTS_H
#define ROGUELIKE_QUESTS_H

extern "C" {
#include <z64math.h>
}

namespace RogueLike {

namespace Quests {

void CompleteQuestById(u8 questId);
void AddQuestById(u8 questId);
void RemoveQuestById(u8 questId);
void UpdateQuestProgress(u8 questId);
void SetQuestProgress(u8 questId, u16 progress);
void ResetQuestProgress(u8 questId);

} // namespace Quests

} // namespace RogueLike

#endif