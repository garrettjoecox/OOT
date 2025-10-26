#pragma once
#ifndef ROGUELIKE_H
#define ROGUELIKE_H

#include <z64math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    RL_ATTACK,
    RL_DEFENSE,
    RL_MAX,
} RoguelikeStats;

#ifdef __cplusplus
}

namespace RogueLike {

void Init();
void RegisterMenu();

void SpawnXPOrb(Vec3f spawnPos, int32_t amount);
void SpawnXPGroup(Vec3f spawnPos, int32_t amount);

} // namespace RogueLike

#endif

#endif // ROGUELIKE_H