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

std::vector<RogueLikeQuestObject> activeQuests;

void TableCellVerticalCenteredText(ImVec4 color, const char* text) {
    float textHeight = ImGui::GetTextLineHeight();
    float offsetX = (32.0f - textHeight + 10.0f) * 0.5f;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetX);
    ImGui::TextColored(color, text);
}

void TableCellHorizontalCenteredText(ImVec4 color, const char* text) {
    float cellWidth = ImGui::GetContentRegionAvail().x;
    float textWidth = ImGui::CalcTextSize(text).x;
    float offsetX = (cellWidth - textWidth) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
    ImGui::TextColored(color, text);
}

bool TableCellCenteredImageButton(const char* id, ImTextureID texture) {
    float cellWidth = ImGui::GetContentRegionAvail().x;
    float offsetX = (cellWidth - 46.0f) * 0.5f;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
    return ImGui::ImageButton(id, texture, ImVec2(46.0f, 46.0f));
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
            ImTextureID textureId =
                Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName("ITEM_RUPEE_GREEN");
            ImGui::TableNextColumn();
            ImGui::Image(textureId, ImVec2(46.0f, 46.0f));

            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(1, 1, 1, 1), "Level");

            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(0, 1, 0, 1), std::to_string(RogueLike::XP::GetCurrentLevel()).c_str());

            ImTextureID textureId2 =
                Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName("ITEM_MASK_SKULL");
            ImGui::TableNextColumn();
            ImGui::Image(textureId2, ImVec2(46.0f, 46.0f));

            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(1, 1, 1, 1), "Difficulty");

            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(0, 1, 0, 1),
                                          std::to_string(RogueLike::Difficulty::GetCurrentLevel()).c_str());

            for (auto& stat : rogueLikeStatMap) {
                ImTextureID textureId =
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(stat.second.second);
                std::string statValueStr = gSaveContext.ship.quest.data.rogueLike.stats[stat.first] >= 0 ? "+" : "-";
                statValueStr += std::to_string(gSaveContext.ship.quest.data.rogueLike.stats[stat.first]).c_str();

                ImGui::TableNextColumn();
                ImGui::Image(textureId, ImVec2(46.0f, 46.0f));

                ImGui::TableNextColumn();
                TableCellVerticalCenteredText(ImVec4(1, 1, 1, 1), stat.second.first.c_str());

                ImGui::TableNextColumn();
                TableCellVerticalCenteredText(ImVec4(0, 1, 0, 1), statValueStr.c_str());
            }

            ImGui::EndTable();

            if (ImGui::BeginChild("QuestWindow", ImVec2(300.0f, 0))) {
                if (activeQuests.size() != 0) {
                    ImVec4 completionColor = ImVec4(1, 1, 1, 1);
                    for (auto& quests : activeQuests) {
                        if (quests.questProgress == quests.questGoal) {
                            completionColor = ImVec4(0, 1, 0, 1);
                        }
                        std::string questProgressStr = std::to_string(quests.questProgress).c_str();
                        questProgressStr += " / ";
                        questProgressStr += std::to_string(quests.questGoal).c_str();

                        ImGui::SeparatorText(quests.questName);
                        ImGui::Text(quests.questDescription);
                        TableCellHorizontalCenteredText(completionColor, questProgressStr.c_str());
                        ImGui::Separator();
                    }
                }
                ImGui::EndChild();
            }
        }
        ImGui::EndChild();
    }
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);

    ImGui::End();
}

void RogueLike::GUI::LevelUpWindow::Draw() {
    if (!IsVisible()) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.2f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(4.0f, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
    ImVec2 levelUpWindowSize = ImVec2(0, 0);
    ImVec2 levelUpWindowPlacement = ImVec2(ImGui::GetContentRegionMax().x - levelUpWindowSize.x,
                                           ImGui::GetContentRegionMax().y - levelUpWindowSize.y);
    ImGui::SetNextWindowPos(levelUpWindowPlacement);
    ImGui::SetNextWindowSize(levelUpWindowSize);

    if (ImGui::Begin("Level Up", nullptr,
                     ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings)) {

        TableCellHorizontalCenteredText(ImVec4(0, 1, 0, 1), "LEVEL UP");
        if (ImGui::BeginTable("LevelUpOptions", 3, ImGuiTableFlags_SizingFixedFit)) {
            for (auto& stat : rogueLikeStatMap) {
                ImTextureID textureId =
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(stat.second.second);

                ImGui::TableNextColumn();
                if (TableCellCenteredImageButton(stat.second.first.c_str(), textureId)) {
                    gSaveContext.ship.quest.data.rogueLike.stats[stat.first]++;
                    this->Hide();
                    gPlayState->frameAdvCtx.enabled = false;
                }
                ImGui::Text(stat.second.first.c_str());
            }
            ImGui::EndTable();
        }
        levelUpWindowSize = ImGui::GetWindowSize();
        ImGui::End();
    }

    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(2);
}

std::shared_ptr<RogueLike::GUI::StartingSelectionWindow> mStartingSelectionWindow;
std::shared_ptr<RogueLike::GUI::HUDWindow> mHUDWindow;
std::shared_ptr<RogueLike::GUI::LevelUpWindow> mLevelUpWindow;

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

    mLevelUpWindow =
        std::make_shared<RogueLike::GUI::LevelUpWindow>(CVAR_WINDOW("RogueLikeLevelUp"), "RogueLike Level Up");
    gui->AddGuiWindow(mLevelUpWindow);

    COND_HOOK(OnExitGame, true, [](int32_t fileNum) {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
        mLevelUpWindow->Hide();
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
    mLevelUpWindow->Hide();

    COND_HOOK(OnPlayerUpdate, IS_ROGUELIKE, [] {
        if (mStartingSelectionWindow->IsVisible() || mLevelUpWindow->IsVisible()) {
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
