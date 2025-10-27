#ifndef ROGUELIKE_ACTOR_BEHAVIOR_H
#define ROGUELIKE_ACTOR_BEHAVIOR_H

namespace RogueLike {

namespace ActorBehavior {

void Init();
void OnLoadGame();

void InitEnBoxBehavior();
void InitEnDnsBehavior();
void InitEnIshiBehavior();
void InitEnKusaBehavior();
void InitEnWood02Behavior();
void InitObjTsuboBehavior();

} // namespace ActorBehavior

} // namespace RogueLike

#endif
