#ifndef ROGUELIKE_H
#define ROGUELIKE_H

#include "GUI/GUI.h"
#include "XP.h"
#include "Difficulty.h"
#include "Quests.h"
#include "Types.h"

extern std::vector<RogueLikeQuestObject> activeQuests;

namespace RogueLike {
extern std::vector<uint32_t> requiredRewards;
} // namespace RogueLike

#endif // ROGUELIKE_H
