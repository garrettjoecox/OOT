#pragma once
#ifndef ROGUELIKE_H
#define ROGUELIKE_H

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

} // namespace RogueLike

#endif

#endif // ROGUELIKE_H