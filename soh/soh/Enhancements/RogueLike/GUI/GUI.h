#ifndef ROGUELIKE_GUI_H
#define ROGUELIKE_GUI_H

#include <libultraship/libultraship.h>

namespace RogueLike {

namespace GUI {

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

void Init();
void OnLoadGame();

} // namespace GUI

} // namespace RogueLike

#endif
