#include "GUI.h"
#include "soh/Enhancements/game-interactor/vanilla-behavior/GIVanillaBehavior.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

void RogueLike::GUI::StartingSelectionWindow::Draw() {
    if (!IsVisible()) {
        return;
    }

    // Full screen overlay
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("RogueLike Starting Selection", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

    ImGui::Text("RogueLike Starting Selection");
    if (ImGui::Button("Start RogueLike Mode")) {
        this->Hide();
        gPlayState->frameAdvCtx.enabled = false;
    }
    ImGui::End();
}

std::shared_ptr<RogueLike::GUI::StartingSelectionWindow> mStartingSelectionWindow;

// Entry point for the module, run once on game boot
void RogueLike::GUI::Init() {
    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();

    mStartingSelectionWindow = std::make_shared<RogueLike::GUI::StartingSelectionWindow>();
    gui->AddGuiWindow(mStartingSelectionWindow);

    COND_HOOK(OnExitGame, true, [](int32_t fileNum) {
        mStartingSelectionWindow->Hide();
    });
}

void RogueLike::GUI::OnLoadGame() {
    if (IS_ROGUELIKE) {
        mStartingSelectionWindow->Show();
    } else {
        mStartingSelectionWindow->Hide();
    }

    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, [] {
        if (mStartingSelectionWindow->IsVisible()) {
            gPlayState->frameAdvCtx.enabled = true;
        } else {
            gPlayState->frameAdvCtx.enabled = false;
        }
    });
}
