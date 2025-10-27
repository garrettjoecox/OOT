#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

std::map<RoguelikeStats, std::pair<std::string, std::string>> rogueLikeStatMap = {
    { RL_ATTACK, { "Attack", "ITEM_SWORD_MASTER" } },
    { RL_DEFENSE, { "Defense", "ITEM_SHIELD_HYLIAN" } },
};

void TableCellCenteredText(ImVec4 color, const char* text) {
    float textHeight = ImGui::GetTextLineHeight();
    float offsetY = (32.0f - textHeight + 10.0f) * 0.5f;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);
    ImGui::TextColored(color, text);
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

    ImGui::Begin("RogueLike HUD", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);

    // Progress bar based on experience points
    ImGui::ProgressBar(RogueLike::XP::GetProgressToNextLevel(), ImVec2(-1, 0));
    ImGui::ProgressBar(RogueLike::Difficulty::GetProgressToNextLevel(), ImVec2(-1, 0));

    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
    if (ImGui::BeginChild("StatsWindow")) {
        if (ImGui::BeginTable("StatsList", 3, ImGuiTableFlags_SizingFixedFit)) {
            ImTextureID textureId = Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName("ITEM_RUPEE_GREEN");
            ImGui::TableNextColumn();
            ImGui::Image(textureId, ImVec2(46.0f, 46.0f));

            ImGui::TableNextColumn();
            TableCellCenteredText(ImVec4(1, 1, 1, 1), "Level");

            ImGui::TableNextColumn();
            TableCellCenteredText(ImVec4(0, 1, 0, 1), std::to_string(RogueLike::XP::GetCurrentLevel()).c_str());

            ImTextureID textureId2 = Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName("ITEM_MASK_SKULL");
            ImGui::TableNextColumn();
            ImGui::Image(textureId2, ImVec2(46.0f, 46.0f));

            ImGui::TableNextColumn();
            TableCellCenteredText(ImVec4(1, 1, 1, 1), "Difficulty");

            ImGui::TableNextColumn();
            TableCellCenteredText(ImVec4(0, 1, 0, 1), std::to_string(RogueLike::Difficulty::GetCurrentLevel()).c_str());

            for (auto& stat : rogueLikeStatMap) {
                ImTextureID textureId =
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(stat.second.second);
                std::string statValueStr = gSaveContext.ship.quest.data.rogueLike.stats[stat.first] >= 0 ? "+" : "-";
                statValueStr += std::to_string(gSaveContext.ship.quest.data.rogueLike.stats[stat.first]).c_str();

                ImGui::TableNextColumn();
                ImGui::Image(textureId, ImVec2(46.0f, 46.0f));

                ImGui::TableNextColumn();
                TableCellCenteredText(ImVec4(1, 1, 1, 1), stat.second.first.c_str());

                ImGui::TableNextColumn();
                TableCellCenteredText(ImVec4(0, 1, 0, 1), statValueStr.c_str());
            }

            ImGui::EndTable();
        }
        ImGui::EndChild();
    }
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);

    ImGui::End();
}

std::shared_ptr<RogueLike::GUI::StartingSelectionWindow> mStartingSelectionWindow;
std::shared_ptr<RogueLike::GUI::HUDWindow> mHUDWindow;

// Entry point for the module, run once on game boot
static void InitRogueLikeGUI() {
    CVarClear(CVAR_WINDOW("RogueLikeStartingSelection"));
    CVarClear(CVAR_WINDOW("RogueLikeHUD"));

    auto gui = Ship::Context::GetInstance()->GetWindow()->GetGui();

    mStartingSelectionWindow = std::make_shared<RogueLike::GUI::StartingSelectionWindow>(
        CVAR_WINDOW("RogueLikeStartingSelection"), "RogueLike Starting Selection");
    gui->AddGuiWindow(mStartingSelectionWindow);

    mHUDWindow = std::make_shared<RogueLike::GUI::HUDWindow>(CVAR_WINDOW("RogueLikeHUD"), "RogueLike HUD");
    gui->AddGuiWindow(mHUDWindow);

    COND_HOOK(OnExitGame, true, [](int32_t fileNum) {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
    });
}

static void OnLoadGame() {
    if (IS_ROGUELIKE) {
        mStartingSelectionWindow->Show();
        mHUDWindow->Show();
    } else {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
    }

    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, [] {
        if (mStartingSelectionWindow->IsVisible()) {
            mHUDWindow->Hide();
            gPlayState->frameAdvCtx.enabled = true;
        } else {
            mHUDWindow->Show();
            gPlayState->frameAdvCtx.enabled = false;
        }
    });
}

static RegisterShipInitFunc initFunc(InitRogueLikeGUI, {});
static RegisterShipInitFunc initFunc2(OnLoadGame, { "IS_ROGUELIKE" });
