#include "ArchipelagoSettingsWindow.h"
#include "Archipelago.h"

#include "soh/SohGui/UIWidgets.hpp"
#include "soh/SohGui/SohGui.hpp"
#include "soh/Network/Archipelago/ArchipelagoConsoleWindow.h"
#include "soh/SaveManager.h"

void ArchipelagoSettingsWindow::DrawElement() {
    ArchipelagoClient& apClient = ArchipelagoClient::GetInstance();

    ImGui::SeparatorText("Connection info");

    UIWidgets::PushStyleCombobox(THEME_COLOR);
    ImGui::PushStyleColor(ImGuiCol_Border, UIWidgets::ColorValues.at(THEME_COLOR));

    ImGui::Text("Server Address");
    UIWidgets::CVarInputString("##ArchipelagoServerAddress", CVAR_REMOTE_ARCHIPELAGO("ServerAddress"),
                               UIWidgets::InputOptions()
                                   .Color(THEME_COLOR)
                                   .PlaceholderText("archipelago.gg:38281")
                                   .DefaultValue("archipelago.gg:38281")
                                   .Size(ImVec2(ImGui::GetFontSize() * 15, 0))
                                   .LabelPosition(UIWidgets::LabelPositions::None));
    ImGui::Text("Slot Name");
    UIWidgets::CVarInputString("##ArchipelagoSlotName", CVAR_REMOTE_ARCHIPELAGO("SlotName"),
                               UIWidgets::InputOptions()
                                   .Color(THEME_COLOR)
                                   .Size(ImVec2(ImGui::GetFontSize() * 15, 0))
                                   .LabelPosition(UIWidgets::LabelPositions::None));
    ImGui::Text("Password (leave blank for no password)");
    UIWidgets::CVarInputString("##ArchipelagoPassword", CVAR_REMOTE_ARCHIPELAGO("Password"),
                               UIWidgets::InputOptions()
                                   .Color(THEME_COLOR)
                                   .IsSecret(true)
                                   .Size(ImVec2(ImGui::GetFontSize() * 15, 0))
                                   .LabelPosition(UIWidgets::LabelPositions::None));
    ImGui::PopStyleColor();
    UIWidgets::PopStyleCombobox();

    if (!apClient.IsConnected()) {
        if (UIWidgets::Button("Connect", UIWidgets::ButtonOptions().Color(THEME_COLOR).Size(ImVec2(0.0, 0.0)))) {
            bool success = apClient.StartClient();
        }
    } else {
        if (UIWidgets::Button("Disconnect", UIWidgets::ButtonOptions().Color(THEME_COLOR).Size(ImVec2(0.0, 0.0)))) {
            bool success = apClient.StopClient();
        }
    }

    ImGui::SameLine();

    uint8_t clientStatus = apClient.GetConnectionStatus();
    switch (clientStatus) {
        case 1:
        case 2:
        case 3:
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
            ImGui::Text("Connecting...");
            break;
        case 4:
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5f, 1.0f, 0.5f, 1.0f));
            ImGui::Text("Connected");
            break;
        default:
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.5f, 1.0f));
            ImGui::Text("Not Connected");
            break;
    }
    ImGui::PopStyleColor();

    ImGui::SeparatorText("Additional Options");
    if (UIWidgets::CVarCheckbox(
            "Death Link", CVAR_REMOTE_ARCHIPELAGO("DeathLink"),
            UIWidgets::CheckboxOptions().Color(THEME_COLOR).Tooltip("You die, others die. Others die, you die!"))) {
        apClient.SetDeathLinkTag();
    }
    UIWidgets::CVarCheckbox(
        "Shuffle Entrances", CVAR_REMOTE_ARCHIPELAGO("ShuffleEntrances"),
        UIWidgets::CheckboxOptions()
            .Color(THEME_COLOR)
            .Tooltip(
                "With this checked, pull in a spoiler with entrances shuffled and create a new AP save and your "
                "entrances will match the spoiler. Uncheck and start a new save file to unshuffle entrances again."));
};

void ArchipelagoSettingsWindow::InitElement() {
    SaveManager::Instance->AddLoadFunction("archipelagoData", 1, LoadArchipelagoData);
    SaveManager::Instance->AddSaveFunction("archipelagoData", 1, SaveArchipelagoData, true, SECTION_PARENT_NONE);
    SaveManager::Instance->AddInitFunction(InitArchipelagoData);
}
