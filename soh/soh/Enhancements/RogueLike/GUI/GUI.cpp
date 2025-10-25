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

void RogueLike::GUI::HUDWindow::Draw() {
    if (!IsVisible()) {
        return;
    }

    // Full screen overlay
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::Begin("RogueLike HUD", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

    // Progress bar based on experience points
    float experience = gSaveContext.ship.quest.data.rogueLike.experiencePoints;
    float nextLevelExp = 100;
    float progress = experience / nextLevelExp;
    ImGui::ProgressBar(progress, ImVec2(-1, 0));

    ImGui::End();
}

std::shared_ptr<RogueLike::GUI::StartingSelectionWindow> mStartingSelectionWindow;
std::shared_ptr<RogueLike::GUI::HUDWindow> mHUDWindow;

// Entry point for the module, run once on game boot
void RogueLike::GUI::Init() {
    CVarClear(CVAR_WINDOW("RogueLikeStartingSelection"));
    CVarClear(CVAR_WINDOW("RogueLikeHUD"));

    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();

    mStartingSelectionWindow = std::make_shared<RogueLike::GUI::StartingSelectionWindow>(CVAR_WINDOW("RogueLikeStartingSelection"), "RogueLike Starting Selection");
    gui->AddGuiWindow(mStartingSelectionWindow);

    mHUDWindow = std::make_shared<RogueLike::GUI::HUDWindow>(CVAR_WINDOW("RogueLikeHUD"), "RogueLike HUD");
    gui->AddGuiWindow(mHUDWindow);

    COND_HOOK(OnExitGame, true, [](int32_t fileNum) {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
    });
}

void RogueLike::GUI::OnLoadGame() {
    if (IS_ROGUELIKE) {
        mStartingSelectionWindow->Show();
        mHUDWindow->Show();
    } else {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
    }

    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, [] {
        if (mStartingSelectionWindow->IsVisible()) {
            gPlayState->frameAdvCtx.enabled = true;
        } else {
            gPlayState->frameAdvCtx.enabled = false;
        }
    });
}
