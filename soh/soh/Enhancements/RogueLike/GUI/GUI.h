#ifndef ROGUELIKE_GUI_H
#define ROGUELIKE_GUI_H

#include <libultraship/libultraship.h>
#include <vector>
#include <string>
#include "soh/Enhancements/RogueLike/Choices.hpp"

namespace RogueLike {

namespace GUI {

void BeginFullscreenDimmed(const char* windowName);
RogueLike::Choices::ChoiceCard* DrawChooseScreen(std::string heading,
                                                 std::vector<RogueLike::Choices::ChoiceCard>& allChoices, int rolls);

class StartingSelectionWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    void Draw() override;
    ~StartingSelectionWindow(){};

  protected:
    void InitElement() override{};
    void DrawElement() override{};
    void UpdateElement() override{};
};

class HUDWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    void Draw() override;
    ~HUDWindow(){};

  protected:
    void InitElement() override{};
    void DrawElement() override{};
    void UpdateElement() override{};
};

class LevelUpWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    void Draw() override;
    ~LevelUpWindow(){};

  protected:
    void InitElement() override{};
    void DrawElement() override{};
    void UpdateElement() override{};
};

extern std::shared_ptr<RogueLike::GUI::LevelUpWindow> mLevelUpWindow;

} // namespace GUI

} // namespace RogueLike

#endif
