#ifndef ROGUELIKE_DIFFICULTY_H
#define ROGUELIKE_DIFFICULTY_H

extern "C" {
#include <z64math.h>
}

namespace RogueLike {

namespace Difficulty {

void IndicateActivity();
float GetProgressToNextLevel();
u32 GetCurrentLevel();
u32 ConvertDifficultyToLevel(u32 difficulty);
u32 ConvertLevelToDifficulty(u32 level);
void IncrementDifficulty(u32 amount);
void OnLoadGame();

} // namespace Difficulty

} // namespace RogueLike

#endif
