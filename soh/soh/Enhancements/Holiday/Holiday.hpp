#ifndef HOLIDAY_HPP
#define HOLIDAY_HPP

#include <vector>
#include <functional>
#include <libultraship/libultraship.h>
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/cosmetics/CosmeticsEditor.h"
#include "soh/SohGui/SohMenu.h"
#include "soh/SohGui/SohGui.hpp"
#include "soh/SohGui/UIWidgets.hpp"

inline std::vector<std::function<void()>> holidayDrawFuncs = {};
inline std::vector<std::function<void()>> holidayRegisterFuncs = {};

namespace SohGui {
extern std::shared_ptr<SohMenu> mSohMenu;
}

#endif // HOLIDAY_HPP
