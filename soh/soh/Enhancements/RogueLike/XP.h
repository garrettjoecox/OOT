#ifndef ROGUELIKE_XP_H
#define ROGUELIKE_XP_H

extern "C" {
#include <z64math.h>
}

namespace RogueLike {

namespace XP {

float GetProgressToNextLevel();
u32 GetCurrentLevel();
u32 ConvertXPToLevel(u32 xp);
u32 ConvertLevelToXP(u32 level);
void GrantXP(u32 amount);
void SpawnXPOrb(Vec3f spawnPos, u32 amount);
void SpawnXPGroup(Vec3f spawnPos, u32 amount);

} // namespace XP

} // namespace RogueLike

#endif
