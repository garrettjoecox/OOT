#include "soh/Enhancements/RogueLike/RogueLike.h"

extern "C" {
#include "variables.h"
#include "macros.h"
#include "functions.h"

extern PlayState* gPlayState;
}

typedef enum {
    WINDOW_STATE_LOCATION,
    WINDOW_STATE_ITEM,
    WINDOW_STATE_SONG,
    WINDOW_STATE_APPLY,
} StartingSelectionWindowState;

static StartingSelectionWindowState state = WINDOW_STATE_LOCATION;
static RogueLike::Choices::ChoiceCard* locationChoice = nullptr;
static RogueLike::Choices::ChoiceCard* itemChoice = nullptr;
static RogueLike::Choices::ChoiceCard* songChoice = nullptr;

void RogueLike::GUI::StartingSelectionWindow::Draw() {
    if (!IsVisible()) {
        return;
    }

    BeginFullscreenDimmed("RogueLike Starting Selection");

    switch (state) {
        case WINDOW_STATE_LOCATION: {
            locationChoice = DrawChooseScreen("Where will you begin your journey?", RogueLike::Choices::Locations, 20);
            if (locationChoice != nullptr) {
                state = WINDOW_STATE_ITEM;
            }
        } break;
        case WINDOW_STATE_ITEM: {
            itemChoice = DrawChooseScreen("What will you take?", RogueLike::Choices::Items, 20);

            if (itemChoice != nullptr) {
                state = WINDOW_STATE_SONG;
            }
        } break;
        case WINDOW_STATE_SONG: {
            songChoice = DrawChooseScreen("What is your tune of choice?", RogueLike::Choices::Songs, 20);

            if (songChoice != nullptr) {
                state = WINDOW_STATE_APPLY;
            }
        } break;
        default: {
            // Apply choices
            locationChoice->onSelect(locationChoice->value);
            itemChoice->onSelect(itemChoice->value);
            songChoice->onSelect(songChoice->value);

            // Close window and reload game state
            this->Hide();
            SET_NEXT_GAMESTATE(&gPlayState->state, Play_Init, PlayState);
            gPlayState->state.running = false;

            // Reset state
            state = WINDOW_STATE_LOCATION;
            locationChoice = nullptr;
            itemChoice = nullptr;
            songChoice = nullptr;
        } break;
    }

    ImGui::End();
}
