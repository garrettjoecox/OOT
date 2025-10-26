#ifndef ROGUELIKE_ACTOR_BEHAVIOR_H
#define ROGUELIKE_ACTOR_BEHAVIOR_H

#include "soh/Enhancements/RogueLike/RogueLike.h"

namespace RogueLike {

namespace ActorBehavior {

void Init();
void OnLoadGame();

void InitEnBoxBehavior();
void InitEnIshiBehavior();
void InitEnKusaBehavior();
void InitEnWood02Behavior();
void InitObjTsuboBehavior();

} // namespace ActorBehavior

} // namespace RogueLike

#endif
