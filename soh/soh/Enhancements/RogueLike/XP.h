#ifndef ROGUELIKE_XP_H
#define ROGUELIKE_XP_H

#include "soh/Enhancements/custom-item/CustomItem.h"

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
void SpawnXPOrb(Vec3f spawnPos, u32 amount, int16_t flags = CustomItem::STOP_BOBBING | CustomItem::TOSS_ON_SPAWN);
void SpawnXPGroup(Vec3f spawnPos, u32 amount);
void UpdatePlayerStats();

} // namespace XP

} // namespace RogueLike

#endif
