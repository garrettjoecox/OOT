#ifndef ROGUELIKE_GUI_H
#define ROGUELIKE_GUI_H

#include "soh/Enhancements/RogueLike/RogueLike.h"
#include <libultraship/libultraship.h>

namespace RogueLike {

namespace GUI {

class StartingSelectionWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    void Draw() override;
    ~StartingSelectionWindow(){};

  protected:
    void InitElement() override {};
    void DrawElement() override {};
    void UpdateElement() override {};
};

void Init();
void OnLoadGame();

} // namespace GUI

} // namespace RogueLike

#endif
