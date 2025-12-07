#include "soh/Enhancements/RogueLike/RogueLike.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/ShipInit.hpp"
#include "soh/SohGui/SohMenu.h"
#include "soh/Enhancements/randomizer/3drando/random.hpp"

extern "C" {
#include "variables.h"

extern PlayState* gPlayState;
}

namespace SohGui {
extern std::shared_ptr<SohMenu> mSohMenu;
}

#define QUEST_TO_TEXTURE(id) \
    { id, #id }

std::map<uint32_t, const char*> questToTexture = {
    QUEST_TO_TEXTURE(QUEST_MEDALLION_FOREST), QUEST_TO_TEXTURE(QUEST_MEDALLION_FIRE),
    QUEST_TO_TEXTURE(QUEST_MEDALLION_WATER),  QUEST_TO_TEXTURE(QUEST_MEDALLION_SPIRIT),
    QUEST_TO_TEXTURE(QUEST_MEDALLION_SHADOW), QUEST_TO_TEXTURE(QUEST_MEDALLION_LIGHT),
    QUEST_TO_TEXTURE(QUEST_KOKIRI_EMERALD),   QUEST_TO_TEXTURE(QUEST_GORON_RUBY),
    QUEST_TO_TEXTURE(QUEST_ZORA_SAPPHIRE),    QUEST_TO_TEXTURE(QUEST_STONE_OF_AGONY),
    QUEST_TO_TEXTURE(QUEST_GERUDO_CARD),      QUEST_TO_TEXTURE(QUEST_SKULL_TOKEN),
};

void RogueLike::GUI::BeginFullscreenDimmed(const char* windowName) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin(windowName, nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();
}

static std::vector<RogueLike::Choices::ChoiceCard*> choices = {};
static float rollTimer = 0.0f;
static int rollsRemaining = 0;

RogueLike::Choices::ChoiceCard*
RogueLike::GUI::DrawChooseScreen(std::string heading, std::vector<RogueLike::Choices::ChoiceCard>& allChoices,
                                 int rolls) {
    RogueLike::Choices::ChoiceCard* selectedChoice = nullptr;

    ImVec2 outerCardSize = ImVec2(300, 400);
    ImVec2 innerCardSize = ImVec2(outerCardSize.x - 40, outerCardSize.y - 40);
    ImVec2 iconSize = ImVec2(125, 125);

    // Heading
    ImGui::SetWindowFontScale(2.0f);
    ImGui::SetCursorPosY(ImGui::GetWindowHeight() / 2 - (outerCardSize.y / 2) - 100);
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(heading.c_str()).x) / 2);
    ImGui::Text("%s", heading.c_str());
    ImGui::SetWindowFontScale(1.0f);

    // Cards
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

    if (choices.size() == 0) {
        choices = RogueLike::Choices::Choose3Max(allChoices);
        rollTimer = 0.0f;
        if (choices.size() > 2) {
            rollsRemaining = rolls;
            choices.resize(2);
        } else {
            rollsRemaining = 0;
        }
    }

    if (rollsRemaining > 0) {
        rollTimer += ImGui::GetIO().DeltaTime;
        if (rollTimer >= 0.05f) {
            rollTimer = 0.0f;
            rollsRemaining--;
            choices = RogueLike::Choices::Choose3Max(allChoices);
            if (choices.size() > 2) {
                choices.resize(2);
            }
        }
    }

    float cardStartX = (ImGui::GetWindowWidth() - (outerCardSize.x * choices.size())) / 2;
    float cardStartY = ImGui::GetWindowHeight() / 2 - (outerCardSize.y / 2);

    ImGui::SetCursorPosX(cardStartX);
    ImGui::SetCursorPosY(cardStartY);

    static int cachedHoverIndex = -1;
    int hoverIndex = -1;

    for (size_t i = 0; i < choices.size(); i++) {
        if (i > 0) {
            ImGui::SameLine();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
        ImGui::BeginChild(("card" + std::to_string(i)).c_str(), outerCardSize, ImGuiChildFlags_AlwaysUseWindowPadding);
        ImGui::PopStyleVar();
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, (cachedHoverIndex == static_cast<int>(i))
                                                    ? ImVec4(0.2f, 0.2f, 0.2f, 1.0f)
                                                    : ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
        ImGui::BeginChild(("card_content" + std::to_string(i)).c_str(), ImVec2(-1, -1), 0);
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();

        if (choices[i]->textureName.substr(0, 10) == "QUEST_SONG") {
            // Songs are thinner
            iconSize = ImVec2(100, 150);
        }

        ImGui::SetCursorPosX(innerCardSize.x / 2 - iconSize.x / 2);
        ImGui::SetCursorPosY(innerCardSize.y / 2 - iconSize.y / 2 - 20);
        ImTextureID textureId =
            Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(choices[i]->textureName);
        ImGui::Image(textureId, iconSize);

        ImGui::SetCursorPosX(innerCardSize.x / 2 - ImGui::CalcTextSize(choices[i]->name.c_str()).x / 2);
        ImGui::SetCursorPosY(innerCardSize.y - 75);
        if (rollsRemaining == 0) {
            ImGui::Text("%s", choices[i]->name.c_str());
        }

        ImGui::EndChild();
        if (ImGui::IsItemHovered() && rollsRemaining == 0) {
            hoverIndex = static_cast<int>(i);
        }
        if (ImGui::IsItemClicked() && rollsRemaining == 0) {
            selectedChoice = choices[i];
        }
        ImGui::EndChild();
    }

    // Draw button indicators below each card
    for (size_t i = 0; i < choices.size(); i++) {
        // Draw button indicator
        const char* buttonLabel = (i == 0) ? "B" : "A";
        float circleRadius = 30.0f;
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 circleCenter = ImVec2(windowPos.x + cardStartX + (outerCardSize.x * i) + (outerCardSize.x / 2),
                                     windowPos.y + cardStartY + outerCardSize.y + 70);

        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->AddCircleFilled(circleCenter, circleRadius,
                                  rollsRemaining == 0
                                      ? ((i == 0) ? IM_COL32(0, 150, 0, 255) : IM_COL32(20, 20, 190, 255))
                                      : IM_COL32(100, 100, 100, 255));
        drawList->AddCircle(circleCenter, circleRadius, IM_COL32(0, 0, 0, 100), 0, 4.0f);

        ImVec2 textSize = ImGui::CalcTextSize(buttonLabel);
        ImVec2 textPos = ImVec2(circleCenter.x - textSize.x / 2, circleCenter.y - textSize.y / 2);
        drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), buttonLabel);
    }

    if (hoverIndex != -1) {
        cachedHoverIndex = hoverIndex;
    } else {
        cachedHoverIndex = -1;
    }

    ImGui::PopStyleVar();

    if (rollsRemaining == 0) {
        Input* input = &gPlayState->state.input[0];

        if (CHECK_BTN_ANY(input->press.button, BTN_A) && choices.size() > 1) {
            selectedChoice = choices[1];
            input->press.button &= ~BTN_A;
        }
        if (CHECK_BTN_ANY(input->press.button, BTN_B)) {
            selectedChoice = choices[0];
            input->press.button &= ~BTN_B;
        }
    }

    if (selectedChoice != nullptr) {
        choices.clear();
    }
    return selectedChoice;
}

std::map<RoguelikeStats, std::pair<std::string, std::string>> rogueLikeStatMap = {
    { RL_HEALTH, { "Health", "ITEM_HEART_CONTAINER" } },
    { RL_ATTACK, { "Attack", "ITEM_SWORD_MASTER" } },
    { RL_DEFENSE, { "Defense", "ITEM_SHIELD_HYLIAN" } },
    { RL_SPEED, { "Speed", "ITEM_MASK_BUNNY" } },
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
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 9.0f);
            ImGui::ProgressBar(RogueLike::XP::GetProgressToNextLevel(), ImVec2(200, 0),
                               (std::to_string(RogueLike::XP::GetCurrentLevel()) + " (" +
                                std::to_string(static_cast<int>(RogueLike::XP::GetProgressToNextLevel() * 100)) + "%)")
                                   .c_str());

            ImTextureID textureId2 =
                Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName("ITEM_MASK_SKULL");
            ImGui::TableNextColumn();
            ImGui::Image(textureId2, ImVec2(46.0f, 46.0f));

            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(1, 1, 1, 1), "Difficulty");

            ImGui::TableNextColumn();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 9.0f);
            ImGui::ProgressBar(
                RogueLike::Difficulty::GetProgressToNextLevel(), ImVec2(200, 0),
                (std::to_string(RogueLike::Difficulty::GetCurrentLevel()) + " (" +
                 std::to_string(static_cast<int>(RogueLike::Difficulty::GetProgressToNextLevel() * 100)) + "%)")
                    .c_str());

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

            ImGui::TableNextColumn();
            ImGui::TableNextColumn();
            TableCellVerticalCenteredText(ImVec4(1, 1, 1, 1), "Required Dungeon Rewards:");
            ImGui::TableNextColumn();
            ImGui::TableNextColumn();
            ImGui::TableNextColumn();
            for (auto& reward : RogueLike::requiredRewards) {
                if (reward != RogueLike::requiredRewards[0]) {
                    ImGui::SameLine();
                }
                auto tint = CHECK_QUEST_ITEM(reward) ? ImVec4(1, 1, 1, 1) : ImVec4(1, 1, 1, 0.5f);
                ImTextureID textureId =
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(questToTexture[reward]);
                ImGui::Image(textureId, ImVec2(25.0f, 25.0f), ImVec2(0.0f, 0.0f), ImVec2(1, 1), tint,
                             ImVec4(0, 0, 0, 0));
            }

            ImGui::EndTable();

            if (ImGui::BeginChild("QuestWindow", ImVec2(300.0f, 0))) {
                if (activeQuests.size() != 0) {
                    ImVec4 completionColor = ImVec4(1, 1, 1, 1);
                    for (auto& quests : activeQuests) {
                        if (quests.questProgress == quests.questGoal || quests.questStatus == RL_QUEST_COMPLETE) {
                            completionColor = ImVec4(0, 1, 0, 1);
                        }

                        ImGui::SeparatorText(quests.questName);
                        if (quests.questStatus != RL_QUEST_COMPLETE) {
                            ImGui::Text(quests.questDescription);
                            std::string questProgressStr = std::to_string(quests.questProgress).c_str();
                            questProgressStr += " / ";
                            questProgressStr += std::to_string(quests.questGoal).c_str();
                            TableCellHorizontalCenteredText(completionColor, questProgressStr.c_str());
                        } else {
                            TableCellHorizontalCenteredText(completionColor, "Quest Complete");
                        }

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

    SohGui::mSohMenu->AddSidebarEntry("Holiday", "RogueLike", 2);
    WidgetPath path = { "Holiday", "RogueLike", SECTION_COLUMN_2 };
    SohGui::mSohMenu->AddWidget(path, "RogueLikeRight", WIDGET_CUSTOM).CustomFunction([](WidgetInfo& info) {
        if (UIWidgets::Button("Reset All", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            CVarSetFloat("gRogueLike.BaseDifficulty", 5000.0f);
            CVarSetFloat("gRogueLike.DifficultyGrowthRate", 1.3f);
            CVarSetFloat("gRogueLike.BaseXP", 100.0f);
            CVarSetFloat("gRogueLike.XPGrowthRate", 1.3f);
            CVarSetInteger("gRogueLike.EnemyPlateMax", 3);
            CVarSetInteger("gRogueLike.EnemyPlateChance", 25);

            CVarSetInteger("gRogueLike.XPDrop.Enemies", 50);
            CVarSetInteger("gRogueLike.XPDrop.Bosses", 200);
            CVarSetInteger("gRogueLike.XPDrop.BusinessScrubs", 100);
            CVarSetInteger("gRogueLike.XPDrop.Chests", 50);
            CVarSetInteger("gRogueLike.XPDrop.Grass", 20);
            CVarSetInteger("gRogueLike.XPDrop.Pots", 20);
            CVarSetInteger("gRogueLike.XPDrop.Rocks", 20);
            CVarSetInteger("gRogueLike.XPDrop.Trees", 20);
        }

        ImGui::SeparatorText("Scaling Options:");

        UIWidgets::CVarSliderFloat(
            "Base Difficulty", "gRogueLike.BaseDifficulty",
            UIWidgets::FloatSliderOptions().Min(0.0f).Max(10000.0f).DefaultValue(5000.0f).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderFloat(
            "Difficulty Growth Rate", "gRogueLike.DifficultyGrowthRate",
            UIWidgets::FloatSliderOptions().Min(0.0f).Max(5.0f).DefaultValue(1.3f).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderFloat(
            "Base XP Req", "gRogueLike.BaseXP",
            UIWidgets::FloatSliderOptions().Min(0.0f).Max(1000.0f).DefaultValue(100.0f).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderFloat(
            "XP Growth Rate", "gRogueLike.XPGrowthRate",
            UIWidgets::FloatSliderOptions().Min(0.0f).Max(5.0f).DefaultValue(1.3f).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Maximum Enemies Plated", "gRogueLike.EnemyPlateMax",
            UIWidgets::IntSliderOptions().Min(0).Max(10).DefaultValue(3).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Chance of Enemy Plating", "gRogueLike.EnemyPlateChance",
            UIWidgets::IntSliderOptions().Min(0).Max(100).DefaultValue(25).Size(ImVec2(300.0f, 0.0f)));

        ImGui::SeparatorText("XP Drop Rates:");

        UIWidgets::CVarSliderInt(
            "Enemies", "gRogueLike.XPDrop.Enemies",
            UIWidgets::IntSliderOptions().Min(1).Max(1000).DefaultValue(50).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Bosses", "gRogueLike.XPDrop.Bosses",
            UIWidgets::IntSliderOptions().Min(1).Max(5000).DefaultValue(200).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Business Scrubs", "gRogueLike.XPDrop.BusinessScrubs",
            UIWidgets::IntSliderOptions().Min(1).Max(5000).DefaultValue(100).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Chests", "gRogueLike.XPDrop.Chests",
            UIWidgets::IntSliderOptions().Min(1).Max(1000).DefaultValue(50).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Grass", "gRogueLike.XPDrop.Grass",
            UIWidgets::IntSliderOptions().Min(1).Max(5000).DefaultValue(20).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Pots", "gRogueLike.XPDrop.Pots",
            UIWidgets::IntSliderOptions().Min(1).Max(1000).DefaultValue(20).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Rocks", "gRogueLike.XPDrop.Rocks",
            UIWidgets::IntSliderOptions().Min(1).Max(5000).DefaultValue(20).Size(ImVec2(300.0f, 0.0f)));

        UIWidgets::CVarSliderInt(
            "Trees", "gRogueLike.XPDrop.Trees",
            UIWidgets::IntSliderOptions().Min(1).Max(5000).DefaultValue(20).Size(ImVec2(300.0f, 0.0f)));
    });

    path = { "Holiday", "RogueLike", SECTION_COLUMN_1 };
    SohGui::mSohMenu->AddWidget(path, "RogueLikeLeft", WIDGET_CUSTOM).CustomFunction([](WidgetInfo& info) {
        ImGui::TextWrapped(
            "RogueLike mode is an unpolished proof of concept that enables you to play through the game doing "
            "various things to gain XP and gaining items and progression through random rolls instead of finding them "
            "at specific points in the game. There are various settings to tweak the balance on the right hand panel, "
            "the current balance has not really been heavily tested so feel free to experiment and share your "
            "findings. Also if there is interest some one is welcome to pick this up and polish it into a more "
            "complete mode, all of it is open source.\n\n"
            "\n"
            "To begin, start a new file and select the RogueLike quest mode. Your goal is to beat a random selection "
            "of dungeons, which will grant you Ganon's boss key and allow you to finish the game.");

        ImGui::SeparatorText("Cheats:");

        if (!IS_ROGUELIKE) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Must be in a RogueLike save");
            return;
        }

        if (UIWidgets::Button("Add XP Level", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            RogueLike::XP::GrantXP(RogueLike::XP::ConvertLevelToXP(RogueLike::XP::GetCurrentLevel() + 1) -
                                   gSaveContext.ship.quest.data.rogueLike.xp + 1);
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Remove XP Level", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            gSaveContext.ship.quest.data.rogueLike.xp =
                RogueLike::XP::ConvertLevelToXP(RogueLike::XP::GetCurrentLevel() - 1);
        }
        if (UIWidgets::Button("Add Difficulty Level", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            RogueLike::Difficulty::IncrementDifficulty(
                RogueLike::Difficulty::ConvertLevelToDifficulty(RogueLike::Difficulty::GetCurrentLevel() + 1) -
                gSaveContext.ship.quest.data.rogueLike.difficulty + 1);
        }
        ImGui::SameLine();
        if (UIWidgets::Button("Remove Difficulty Level", UIWidgets::ButtonOptions().Size(UIWidgets::Sizes::Inline))) {
            gSaveContext.ship.quest.data.rogueLike.difficulty =
                RogueLike::Difficulty::ConvertLevelToDifficulty(RogueLike::Difficulty::GetCurrentLevel() - 1);
        }

        std::string statPlusValue = "";
        std::string statMinusValue = "";
        if (ImGui::BeginTable("Stat Testing", 2)) {
            for (auto& stat : rogueLikeStatMap) {
                ImTextureID textureId =
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(stat.second.second);
                statPlusValue = "+ ";
                statMinusValue = "- ";
                std::string statValueStr = stat.second.first;
                statPlusValue += statValueStr;
                statMinusValue += statValueStr;

                ImGui::TableNextColumn();
                if (ImGui::ImageButton(statPlusValue.c_str(), textureId, ImVec2(46.0f, 46.0f))) {
                    gSaveContext.ship.quest.data.rogueLike.stats[stat.first]++;
                    RogueLike::XP::UpdatePlayerStats();
                }
                ImGui::TextColored(ImVec4(0, 1, 0, 1), statPlusValue.c_str());

                ImGui::TableNextColumn();
                if (ImGui::ImageButton(statMinusValue.c_str(), textureId, ImVec2(46.0f, 46.0f))) {
                    gSaveContext.ship.quest.data.rogueLike.stats[stat.first]--;
                    RogueLike::XP::UpdatePlayerStats();
                }
                ImGui::TextColored(ImVec4(1, 0, 0, 1), statMinusValue.c_str());
            }
            ImGui::EndTable();
        }
    });

    COND_HOOK(OnExitGame, true, [](int32_t fileNum) {
        mStartingSelectionWindow->Hide();
        mHUDWindow->Hide();
        mLevelUpWindow->Hide();
    });
}

static void OnLoadGame() {
    mStartingSelectionWindow->Hide();
    mHUDWindow->Hide();
    mLevelUpWindow->Hide();

    if (IS_ROGUELIKE) {
        if (gSaveContext.ship.quest.data.rogueLike.lastActivity == 0) {
            RogueLike::Difficulty::IndicateActivity();
            mStartingSelectionWindow->Show();
        }
    }

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

static RegisterMenuInitFunc menuInitFunc(InitRogueLikeGUI);
static RegisterShipInitFunc initFunc2(OnLoadGame, { "IS_ROGUELIKE" });
