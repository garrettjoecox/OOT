#include "soh/Enhancements/RogueLike/RogueLike.h"

extern "C" {
#include "variables.h"
#include "macros.h"
#include "functions.h"

extern PlayState* gPlayState;
}

typedef enum {
    WINDOW_STATE_CHOOSE_TYPE,
    WINDOW_STATE_CHOOSE_CARD,
    WINDOW_STATE_APPLY,
} LevelUpWindowState;

static LevelUpWindowState state = WINDOW_STATE_CHOOSE_TYPE;
static RogueLike::Choices::ChoiceCard* typeChoice = nullptr;
static RogueLike::Choices::ChoiceCard* cardChoice = nullptr;

void RogueLike::GUI::LevelUpWindow::Draw() {
    if (!IsVisible()) {
        return;
    }

    BeginFullscreenDimmed("RogueLike Level Up");

    switch (state) {
        case WINDOW_STATE_CHOOSE_TYPE: {
            typeChoice = DrawChooseScreen("Choose.", RogueLike::Choices::All, 10);
            if (typeChoice != nullptr) {
                state = WINDOW_STATE_CHOOSE_CARD;
            }
        } break;
        case WINDOW_STATE_CHOOSE_CARD: {
            switch (typeChoice->value) {
                case 0: // Stat
                    cardChoice = DrawChooseScreen("Choose.", RogueLike::Choices::Stats, 10);
                    break;
                case 1: // Item
                    cardChoice = DrawChooseScreen("Choose.", RogueLike::Choices::Items, 10);
                    break;
                case 2: // Equipment
                    cardChoice = DrawChooseScreen("Choose.", RogueLike::Choices::Equipment, 10);
                    break;
                case 3: // Song
                    cardChoice = DrawChooseScreen("Choose.", RogueLike::Choices::Songs, 10);
                    break;
                default:
                    break;
            }

            if (cardChoice != nullptr) {
                state = WINDOW_STATE_APPLY;
            }
        } break;
        default: {
            // Apply choices
            cardChoice->onSelect(cardChoice->value);
            RogueLike::XP::UpdatePlayerStats();

            // Close window and continue game
            this->Hide();
            gPlayState->frameAdvCtx.enabled = false;

            // Reset state
            state = WINDOW_STATE_CHOOSE_TYPE;
            typeChoice = nullptr;
            cardChoice = nullptr;
        } break;
    }

    ImGui::End();
}
