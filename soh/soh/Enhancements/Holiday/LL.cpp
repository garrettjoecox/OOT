#include "Holiday.hpp"
#include "LL.h"

extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
extern PlayState* gPlayState;

// TODO: Include anything you need here from C land
}

#define CVAR(v) "gHoliday.Gameplay." v

static ImVec4 customColorZero = RAINBOW_PRESETS[0][0];
static ImVec4 customColorOne = RAINBOW_PRESETS[0][1];
static ImVec4 customColorMinusZero = RAINBOW_PRESETS[0][2];
static ImVec4 customColorMinusOne = RAINBOW_PRESETS[0][3];

ImVec4 Color_LUSToImGui(Color_RGBA8 color) {
    ImVec4 result;

    result.x = color.r / 255.0f;
    result.y = color.g / 255.0f;
    result.z = color.b / 255.0f;
    result.w = color.a / 255.0f;

    return result;
}

Color_RGBA8 Color_ImGuiToLUS(ImVec4 color) {
    Color_RGBA8 result;

    result.r = static_cast<uint8_t>(color.x * 255);
    result.g = static_cast<uint8_t>(color.y * 255);
    result.b = static_cast<uint8_t>(color.z * 255);
    result.a = static_cast<uint8_t>(color.w * 255);

    return result;
}

static void OnConfigurationChanged() {
    Color_RGBA8 c1 = CVarGetColor(CVAR("CustomRainbow1"), Color_ImGuiToLUS(RAINBOW_PRESETS[0][0]));
    Color_RGBA8 c2 = CVarGetColor(CVAR("CustomRainbow2"), Color_ImGuiToLUS(RAINBOW_PRESETS[0][1]));
    Color_RGBA8 c3 = CVarGetColor(CVAR("CustomRainbow3"), Color_ImGuiToLUS(RAINBOW_PRESETS[0][2]));
    Color_RGBA8 c4 = CVarGetColor(CVAR("CustomRainbow4"), Color_ImGuiToLUS(RAINBOW_PRESETS[0][3]));

    customColorZero = Color_LUSToImGui((Color_RGBA8)c1);
    customColorOne = Color_LUSToImGui((Color_RGBA8)c2);
    customColorMinusZero = Color_LUSToImGui((Color_RGBA8)c3);
    customColorMinusOne = Color_LUSToImGui((Color_RGBA8)c4);
}

static void RegisterMenu() {
    WidgetPath path = { "Holiday", "Gameplay", SECTION_COLUMN_1 };

    SohGui::mSohMenu->AddWidget(path, "Custom Rainbows", WIDGET_CVAR_CHECKBOX).CVar(CVAR("EnableCustomRainbows"));

    SohGui::mSohMenu->AddWidget(path, "Color 1", WIDGET_CVAR_COLOR_PICKER)
        .CVar(CVAR("CustomRainbow1"))
        .Options(UIWidgets::ColorPickerOptions().ShowRandom().ShowReset().UseAlpha(false).DefaultValue(
            Color_ImGuiToLUS(RAINBOW_PRESETS[0][0])));
    SohGui::mSohMenu->AddWidget(path, "Color 2", WIDGET_CVAR_COLOR_PICKER)
        .CVar(CVAR("CustomRainbow2"))
        .Options(UIWidgets::ColorPickerOptions().ShowRandom().ShowReset().UseAlpha(false).DefaultValue(
            Color_ImGuiToLUS(RAINBOW_PRESETS[0][1])));
    SohGui::mSohMenu->AddWidget(path, "Color 3", WIDGET_CVAR_COLOR_PICKER)
        .CVar(CVAR("CustomRainbow3"))
        .Options(UIWidgets::ColorPickerOptions().ShowRandom().ShowReset().UseAlpha(false).DefaultValue(
            Color_ImGuiToLUS(RAINBOW_PRESETS[0][2])));
    SohGui::mSohMenu->AddWidget(path, "Color 4", WIDGET_CVAR_COLOR_PICKER)
        .CVar(CVAR("CustomRainbow4"))
        .Options(UIWidgets::ColorPickerOptions().ShowRandom().ShowReset().UseAlpha(false).DefaultValue(
            Color_ImGuiToLUS(RAINBOW_PRESETS[0][3])));

    SohGui::mSohMenu->AddWidget(path, "Presets", WIDGET_SEPARATOR_TEXT);
    SohGui::mSohMenu->AddWidget(path, "Custom Rainbow Presets", WIDGET_CVAR_COMBOBOX)
        .CVar(CVAR("CustomRainbowPreset"))
        .Options(UIWidgets::ComboboxOptions().ComboMap(RAINBOW_PRESET_NAMES))
        .Callback([&](WidgetInfo& info) {
            size_t rainbowPresetIdx = CVarGetInteger(CVAR("CustomRainbowPreset"), 0);
            customColorZero = RAINBOW_PRESETS[rainbowPresetIdx][0];
            customColorOne = RAINBOW_PRESETS[rainbowPresetIdx][1];
            customColorMinusZero = RAINBOW_PRESETS[rainbowPresetIdx][2];
            customColorMinusOne = RAINBOW_PRESETS[rainbowPresetIdx][3];

            CVarSetColor(CVAR("CustomRainbow1.Value"), Color_ImGuiToLUS(customColorZero));
            CVarSetColor(CVAR("CustomRainbow2.Value"), Color_ImGuiToLUS(customColorOne));
            CVarSetColor(CVAR("CustomRainbow3.Value"), Color_ImGuiToLUS(customColorMinusZero));
            CVarSetColor(CVAR("CustomRainbow4.Value"), Color_ImGuiToLUS(customColorMinusOne));
            CVarSave();
        });

    SohGui::mSohMenu->AddWidget(path, "Do Something With Pots", WIDGET_CVAR_CHECKBOX).CVar(CVAR("DoSomethingWithPots"));
}

// static RegisterShipInitFunc initFunc(OnConfigurationChanged);
// static RegisterMenuInitFunc menuInitFunc(RegisterMenu);
