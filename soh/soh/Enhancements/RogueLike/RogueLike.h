#ifndef ROGUELIKE_H
#define ROGUELIKE_H

#include <z64math.h>

namespace RogueLike {

void Init();
void RegisterMenu();

void SpawnXPOrb(Vec3f spawnPos, int32_t amount);
void SpawnXPGroup(Vec3f spawnPos, int32_t amount);

} // namespace RogueLike

#endif
