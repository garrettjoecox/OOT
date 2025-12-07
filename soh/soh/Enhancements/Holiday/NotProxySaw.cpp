#include "Holiday.hpp"
#include <libultraship/libultraship.h>
#include "soh/SohGui/UIWidgets.hpp"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/custom-message/CustomMessageManager.h"
#include "include/message_data_fmt.h"
#include "soh/Network/Archipelago/Archipelago.h"

extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
extern PlayState* gPlayState;
}

#define CVAR(v) "gHoliday.Gameplay." v

int dialogIndex = 0;
int affection = 0;
int TARGET_AFFECTION = 10;
struct DialogOption {
    std::string text;
    int affectionChange;
    int nextDialogIndex;
};
struct Dialog {
    std::string ganonText;
    std::vector<DialogOption> options;
};

const std::vector<Dialog> dialogs = { { // 0
                                        "Think you can defeat me? Foolish!",
                                        {
                                            { "You're lonely. You don't have to be.", 3, 1 },
                                            { "I'm here to end this... peacefully.", 1, 2 },
                                            { "I respect a man with ambition.", -1, 3 },
                                        } },
                                      { // 1 - Loneliness path
                                        "Lonely? Power's my only ally.",
                                        {
                                            { "There's more to you than that.", 3, 4 },
                                            { "I get it more than you think.", 5, 6 },
                                            { "Why not let someone in?", 2, 5 },
                                        } },
                                      { // 2 - Peace path
                                        "Peace? It's meaningless here.",
                                        {
                                            { "Maybe you've forgotten peace.", 2, 7 },
                                            { "Power isn't everything.", 4, 8 },
                                            { "Ally, not enemy.. that's my goal.", 1, 9 },
                                        } },
                                      { // 3 - Respect path
                                        "Respect? From you?",
                                        {
                                            { "We're not so different.", 3, 10 },
                                            { "Maybe I admire your strength.", 5, 11 },
                                            { "True power must be earned.", -1, 12 },
                                        } },
                                      { // 4 - Early convergence
                                        "You're... different than I thought.",
                                        {
                                            { "Together, we'd be unstoppable.", 4, 13 },
                                            { "Power won't bring fulfillment.", 3, 14 },
                                            { "Let's change the world.", 5, 15 },
                                        } },
                                      { // 5 - Vulnerability path
                                        "No one has ever... understood before.",
                                        {
                                            { "I want to understand you.", 5, 16 },
                                            { "We all need someone.", 4, 17 },
                                            { "Your guard can come down with me.", 3, 18 },
                                        } },
                                      { // 6 - Shared experience path
                                        "You think you know my struggle?",
                                        {
                                            { "I've faced darkness too.", 4, 19 },
                                            { "We're both outcasts.", 5, 20 },
                                            { "Tell me your story.", 3, 16 },
                                        } },
                                      { // 7 - Memory path
                                        "Peace... I barely remember it.",
                                        {
                                            { "Let me remind you.", 5, 21 },
                                            { "We can create new memories.", 4, 22 },
                                            { "The desert remembers peace.", 2, 23 },
                                        } },
                                      { // 8 - Philosophy path
                                        "Then what IS everything?",
                                        {
                                            { "Connection. Trust. Love.", 5, 24 },
                                            { "Finding your true purpose.", 3, 25 },
                                            { "Balance between power and heart.", 4, 26 },
                                        } },
                                      { // 9 - Alliance path
                                        "An ally? What could you offer me?",
                                        {
                                            { "Companionship you've never known.", 5, 27 },
                                            { "A kingdom rebuilt together.", 3, 28 },
                                            { "Freedom from this endless cycle.", 4, 29 },
                                        } },
                                      { // 10 - Similarity path
                                        "Similar? Explain yourself.",
                                        {
                                            { "We both fight for what we believe.", 3, 30 },
                                            { "We've both been betrayed.", 5, 31 },
                                            { "We're both stronger than we show.", 4, 32 },
                                        } },
                                      { // 11 - Admiration path
                                        "Admire? This isn't a trick?",
                                        {
                                            { "Your determination is inspiring.", 5, 33 },
                                            { "You've overcome so much.", 4, 34 },
                                            { "I see the man behind the power.", 6, 35 },
                                        } },
                                      { // 12 - Challenge path (lower affection)
                                        "Then prove you've earned it!",
                                        {
                                            { "I've earned the right to stand here.", 2, 36 },
                                            { "I'm not here to prove anything to you.", -2, 37 },
                                            { "My actions speak louder than words.", 3, 38 },
                                        } },
                                      { // 13 - Partnership power path
                                        "Unstoppable... together?",
                                        {
                                            { "Your strength and my courage.", 5, 39 },
                                            { "We'd reshape Hyrule as equals.", 4, 40 },
                                            { "Imagine what we could achieve.", 3, 41 },
                                        } },
                                      { // 14 - Fulfillment path
                                        "What could fulfill me then?",
                                        {
                                            { "Someone who sees you, truly.", 6, 42 },
                                            { "A purpose beyond conquest.", 3, 43 },
                                            { "The warmth of genuine connection.", 5, 44 },
                                        } },
                                      { // 15 - Revolution path
                                        "Change the world... how?",
                                        {
                                            { "End this cycle of hatred.", 4, 45 },
                                            { "Build something beautiful together.", 5, 46 },
                                            { "Rewrite our destinies.", 6, 47 },
                                        } },
                                      { // 16 - Understanding convergence
                                        "No one has ever tried to understand...",
                                        {
                                            { "I'm not no one. I'm here.", 6, 48 },
                                            { "Your past shaped you, not defined you.", 4, 49 },
                                            { "Let me be the first.", 5, 50 },
                                        } },
                                      { // 17 - Need path
                                        "Need? I've survived alone this long.",
                                        {
                                            { "Surviving isn't living.", 5, 51 },
                                            { "You don't have to anymore.", 6, 52 },
                                            { "Even the strongest need support.", 4, 53 },
                                        } },
                                      { // 18 - Guard down path
                                        "Why would I lower my guard?",
                                        {
                                            { "Because I'm lowering mine first.", 6, 54 },
                                            { "Trust has to start somewhere.", 4, 55 },
                                            { "You're safe with me.", 5, 56 },
                                        } },
                                      { // 19 - Darkness shared path
                                        "Your darkness... tell me.",
                                        {
                                            { "I've fought my own demons.", 5, 57 },
                                            { "We all have shadows within us.", 4, 58 },
                                            { "But I chose light. You can too.", 3, 59 },
                                        } },
                                      { // 20 - Outcast bond path
                                        "Outcasts... yes. We are.",
                                        {
                                            { "Then let's find belonging in each other.", 7, 60 },
                                            { "We don't have to be alone.", 5, 61 },
                                            { "Our shared pain connects us.", 4, 62 },
                                        } },
                                      { // 21 - Reminder path
                                        "How could you remind me?",
                                        {
                                            { "Close your eyes. Remember the desert wind.", 5, 63 },
                                            { "Through moments like this one.", 6, 64 },
                                            { "Let me show you, not tell you.", 4, 65 },
                                        } },
                                      { // 22 - New memories path
                                        "New memories... with you?",
                                        {
                                            { "Every ending is a new beginning.", 6, 66 },
                                            { "Yes. Better ones than you've known.", 5, 67 },
                                            { "We write our own story from here.", 4, 68 },
                                        } },
                                      { // 23 - Desert memories path
                                        "The desert... my home once.",
                                        {
                                            { "It can be again, differently.", 4, 69 },
                                            { "Home is where the heart is.", 5, 70 },
                                            { "I'd like to see it with you.", 6, 71 },
                                        } },
                                      { // 24 - Love path (high affection)
                                        "Love? You speak of... love?",
                                        {
                                            { "Is that so impossible?", 6, 72 },
                                            { "I think I'm falling for you.", 8, 73 },
                                            { "Love is the strongest power.", 5, 74 },
                                        } },
                                      { // 25 - Purpose path
                                        "My purpose was always power.",
                                        {
                                            { "You're meant for more.", 5, 75 },
                                            { "Purpose can evolve.", 4, 76 },
                                            { "Find purpose in protecting, not destroying.", 3, 77 },
                                        } },
                                      { // 26 - Balance path
                                        "Balance... I've never had that.",
                                        {
                                            { "I'll help you find it.", 6, 78 },
                                            { "We can balance each other.", 7, 79 },
                                            { "It's not too late to learn.", 4, 80 },
                                        } },
                                      { // 27 - Companionship offer
                                        "Companionship? What does that mean?",
                                        {
                                            { "It means you're not alone anymore.", 7, 81 },
                                            { "Someone to share victories and defeats.", 5, 82 },
                                            { "A partner in every sense.", 6, 83 },
                                        } },
                                      { // 28 - Kingdom rebuild path
                                        "Rebuild? After all I've destroyed?",
                                        {
                                            { "Redemption is always possible.", 5, 84 },
                                            { "We build on lessons learned.", 4, 85 },
                                            { "Your past doesn't define your future.", 6, 86 },
                                        } },
                                      { // 29 - Freedom path
                                        "Freedom from the cycle...",
                                        {
                                            { "Break free with me.", 7, 87 },
                                            { "We choose our own fate.", 6, 88 },
                                            { "This doesn't have to be our story.", 5, 89 },
                                        } },
                                      { // 30 - Belief path
                                        "You fight for Hyrule. I fight for...",
                                        {
                                            { "For recognition. I see you.", 6, 90 },
                                            { "We can fight for each other now.", 7, 91 },
                                            { "What we fight for can change.", 4, 92 },
                                        } },
                                      { // 31 - Betrayal bond path
                                        "Betrayed... yes. You know that pain?",
                                        {
                                            { "More than you realize.", 6, 93 },
                                            { "But I won't betray you.", 7, 94 },
                                            { "We can heal together.", 5, 95 },
                                        } },
                                      { // 32 - Hidden strength path
                                        "Stronger than I show?",
                                        {
                                            { "Your vulnerability is strength.", 6, 96 },
                                            { "True strength is opening your heart.", 7, 97 },
                                            { "I see both your power and pain.", 5, 98 },
                                        } },
                                      { // 33 - Inspiration path
                                        "You're... inspired by me?",
                                        {
                                            { "Your resolve never wavered.", 6, 99 },
                                            { "Despite everything, you stood tall.", 7, 100 },
                                            { "That kind of strength is rare.", 5, 101 },
                                        } },
                                      { // 34 - Overcome path
                                        "I've overcome... so much pain.",
                                        {
                                            { "And you don't have to face more alone.", 7, 102 },
                                            { "Let me help carry that burden.", 6, 103 },
                                            { "Your journey shaped a remarkable person.", 5, 104 },
                                        } },
                                      { // 35 - True sight path (very high affection)
                                        "You... you see me? The real me?",
                                        {
                                            { "Every part of you.", 8, 105 },
                                            { "Behind the armor and anger, yes.", 7, 106 },
                                            { "And I want to know you more.", 6, 107 },
                                        } },
                                      { // 36 - Earned respect path
                                        "Perhaps you have earned something...",
                                        {
                                            { "Your respect means everything.", 5, 108 },
                                            { "I've earned a chance.", 4, 109 },
                                            { "Maybe even your trust?", 6, 110 },
                                        } },
                                      { // 37 - Confrontation path (recovery possible)
                                        "Arrogant! Just like I thought!",
                                        {
                                            { "Wait, I didn't mean it like that.", 3, 111 },
                                            { "You're right, I'm sorry.", 4, 112 },
                                            { "Let me start over.", 2, 113 },
                                        } },
                                      { // 38 - Action path
                                        "Actions... like coming here unarmed?",
                                        {
                                            { "I'm armed with only honesty.", 6, 114 },
                                            { "My sword isn't drawn.", 5, 115 },
                                            { "I chose words over weapons.", 7, 116 },
                                        } },
                                      { // 39 - Combined strength
                                        "My strength and your courage...",
                                        {
                                            { "We'd be legendary.", 6, 117 },
                                            { "Nothing could stand in our way.", 5, 118 },
                                            { "But more than that, we'd have each other.", 8, 119 },
                                        } },
                                      { // 40 - Equals path
                                        "Equals? You'd see me as equal?",
                                        {
                                            { "Never as less than.", 7, 81 },
                                            { "Partners in every way.", 8, 83 },
                                            { "Two halves of a greater whole.", 6, 79 },
                                        } },
                                      { // 41 - Achievement dreams
                                        "I've imagined... but never with another.",
                                        {
                                            { "Dream with me now.", 7, 66 },
                                            { "Our achievements, together.", 6, 82 },
                                            { "Let's make it real.", 8, 117 },
                                        } },
                                      { // 42 - True sight deep
                                        "Someone who sees me truly...",
                                        {
                                            { "I see your scars and your dreams.", 8, 105 },
                                            { "Every layer, every truth.", 7, 106 },
                                            { "And I'm not afraid.", 9, 54 },
                                        } },
                                      { // 43 - New purpose
                                        "A purpose beyond conquest...",
                                        {
                                            { "Building instead of destroying.", 6, 84 },
                                            { "Creating a legacy of hope.", 7, 86 },
                                            { "Finding joy in creation.", 5, 76 },
                                        } },
                                      { // 44 - Connection warmth
                                        "Warmth... I've been cold so long.",
                                        {
                                            { "Let me warm your heart.", 9, 65 },
                                            { "You don't have to be cold anymore.", 8, 52 },
                                            { "I'll be your warmth.", 10, 56 },
                                        } },
                                      { // 45 - End hatred
                                        "End the hatred... can it be done?",
                                        {
                                            { "With you by my side, yes.", 8, 88 },
                                            { "We start by choosing love.", 9, 74 },
                                            { "Together, we break the cycle.", 7, 87 },
                                        } },
                                      { // 46 - Build beauty
                                        "Something beautiful... with you?",
                                        {
                                            { "The most beautiful thing.", 9, 73 },
                                            { "A future worth living for.", 8, 86 },
                                            { "Our love could heal Hyrule.", 10, 95 },
                                        } },
                                      { // 47 - Rewrite destiny
                                        "Rewrite our destinies... together...",
                                        {
                                            { "Our story, our way.", 9, 68 },
                                            { "No prophecy can stop us.", 8, 88 },
                                            { "Destiny is what we make it.", 10, 119 },
                                        } },
                                      { // 48 - Here for you
                                        "You're here... for me?",
                                        {
                                            { "Only for you.", 9, 73 },
                                            { "I chose you, Ganondorf.", 10, 94 },
                                            { "And I'm not leaving.", 8, 52 },
                                        } },
                                      { // 49 - Past vs present
                                        "Shaped but not defined...",
                                        {
                                            { "You define yourself now.", 8, 76 },
                                            { "Your future is unwritten.", 7, 86 },
                                            { "Define yourself through love.", 9, 74 },
                                        } },
                                      { // 50 - First to understand
                                        "The first to try...",
                                        {
                                            { "And I'll never stop trying.", 10, 103 },
                                            { "You deserve understanding.", 8, 95 },
                                            { "Let me be your first and last.", 9, 61 },
                                        } },
                                      { // 51 - Living vs surviving
                                        "Living... what is that like?",
                                        {
                                            { "Let me show you.", 9, 65 },
                                            { "It's everything you've missed.", 8, 64 },
                                            { "We'll discover it together.", 10, 66 },
                                        } },
                                      { // 52 - No more alone
                                        "I don't... have to be alone?",
                                        {
                                            { "Never again.", 10, 81 },
                                            { "I'm here, always.", 9, 102 },
                                            { "We'll face everything together.", 8, 53 },
                                        } },
                                      { // 53 - Strongest need support
                                        "Even the strongest...",
                                        {
                                            { "Especially the strongest.", 8, 103 },
                                            { "Let me be your strength.", 9, 97 },
                                            { "We're stronger together.", 10, 119 },
                                        } },
                                      { // 54 - Mutual vulnerability
                                        "You'd... lower yours first?",
                                        {
                                            { "I already have.", 10, 94 },
                                            { "My heart is open to you.", 9, 97 },
                                            { "I trust you completely.", 11, 110 },
                                        } },
                                      { // 55 - Trust begins
                                        "Trust... starting here?",
                                        {
                                            { "Right here, right now.", 9, 64 },
                                            { "With us, with this moment.", 10, 94 },
                                            { "I trust you with everything.", 8, 110 },
                                        } },
                                      { // 56 - Safe haven
                                        "Safe... with you?",
                                        {
                                            { "Always. I promise.", 11, 94 },
                                            { "I'll protect your heart.", 10, 103 },
                                            { "You're safe in my arms.", 12, 60 },
                                        } },
                                      { // 57 - Shared demons
                                        "Your demons... like mine?",
                                        {
                                            { "We can fight them together.", 9, 53 },
                                            { "They don't control us anymore.", 8, 59 },
                                            { "Love conquers all darkness.", 10, 74 },
                                        } },
                                      { // 58 - Universal shadows
                                        "Shadows within us all...",
                                        {
                                            { "But you bring light to mine.", 10, 63 },
                                            { "Let's be each other's light.", 11, 79 },
                                            { "Together we shine brighter.", 9, 118 },
                                        } },
                                      { // 59 - Choose light
                                        "I could... choose light?",
                                        {
                                            { "You already are, by listening.", 9, 48 },
                                            { "Choose me, choose light.", 10, 88 },
                                            { "It's never too late.", 8, 80 },
                                        } },
                                      { // 60 - Belonging together
                                        "Belonging... in each other...",
                                        {
                                            { "You belong with me.", 12, 83 },
                                            { "We're home in each other.", 11, 119 },
                                            { "My heart is your home.", 13, 119 },
                                        } },
                                      { // 61 - Together forever
                                        "Not alone... anymore...",
                                        {
                                            { "Never, ever alone.", 11, 102 },
                                            { "I'll always be here.", 10, 119 },
                                            { "Forever together.", 12, 119 },
                                        } },
                                      { // 62 - Connected pain
                                        "Our shared pain connects us...",
                                        {
                                            { "Now let joy connect us.", 10, 117 },
                                            { "Pain brought us here, love keeps us.", 11, 95 },
                                            { "From pain to paradise.", 9, 51 },
                                        } },
                                      { // 63 - Desert meditation
                                        "The desert wind... I remember...",
                                        {
                                            { "Hold onto that feeling.", 9, 64 },
                                            { "Peace can return.", 10, 69 },
                                            { "I'll be your peace.", 11, 56 },
                                        } },
                                      { // 64 - This moment
                                        "This moment... it feels...",
                                        {
                                            { "Like coming home?", 10, 79 },
                                            { "Like the start of something beautiful?", 11, 66 },
                                            { "Right. It feels right.", 12, 79 },
                                        } },
                                      { // 65 - Show not tell
                                        "Show me... how?",
                                        {
                                            { "Through actions, through devotion.", 10, 114 },
                                            { "Every day, every moment.", 11, 102 },
                                            { "Let me love you.", 12, 73 },
                                        } },
                                      { // 66 - New beginning
                                        "A new beginning... with you...",
                                        {
                                            { "Our greatest adventure.", 11, 117 },
                                            { "Better than any ending.", 10, 117 },
                                            { "The best is yet to come.", 12, 89 },
                                        } },
                                      { // 67 - Better memories
                                        "Better memories... I want that.",
                                        {
                                            { "Then take my hand.", 12, 119 },
                                            { "We'll make them together.", 11, 68 },
                                            { "Starting right now.", 10, 64 },
                                        } },
                                      { // 68 - Write our story
                                        "Our story... from here...",
                                        {
                                            { "The greatest story ever told.", 11, 117 },
                                            { "Written in love, not war.", 12, 116 },
                                            { "A story for the ages.", 10, 89 },
                                        } },
                                      { // 69 - Home differently
                                        "Home, differently... explain.",
                                        {
                                            { "With love, not loneliness.", 10, 119 },
                                            { "Together, not alone.", 11, 119 },
                                            { "Our home, our rules.", 9, 71 },
                                        } },
                                      { // 70 - Heart is home
                                        "Where the heart is...",
                                        {
                                            { "My heart is with you.", 12, 83 },
                                            { "You are my home.", 13, 119 },
                                            { "Home is in your eyes.", 11, 105 },
                                        } },
                                      { // 71 - See together
                                        "You'd... visit my homeland with me?",
                                        {
                                            { "Anywhere you go, I go.", 12, 61 },
                                            { "I want to see your world.", 11, 107 },
                                            { "Your past is part of our future.", 10, 86 },
                                        } },
                                      { // 72 - Love not impossible
                                        "Not impossible... but unexpected.",
                                        {
                                            { "The best things are unexpected.", 11, 117 },
                                            { "Sometimes fate surprises us.", 10, 88 },
                                            { "I love you, Ganondorf.", 13, 73 },
                                        } },
                                      { // 73 - Falling confession
                                        "You're... falling for me?",
                                        {
                                            { "I've already fallen.", 14, -1 },
                                            { "Completely, utterly, truly.", 13, -1 },
                                            { "Catch me?", 12, -1 },
                                        } },
                                      { // 74 - Love strongest power
                                        "Love... the strongest power...",
                                        {
                                            { "And it's ours to share.", 12, 119 },
                                            { "More powerful than the Triforce.", 13, -1 },
                                            { "Let love be our strength.", 11, 97 },
                                        } },
                                      { // 75 - Meant for more
                                        "Meant for more... perhaps...",
                                        {
                                            { "I know you are.", 10, 76 },
                                            { "You're meant for greatness and love.", 11, 101 },
                                            { "Let me prove it to you.", 9, 65 },
                                        } },
                                      { // 76 - Purpose evolves
                                        "Purpose can evolve...",
                                        {
                                            { "Like we evolve together.", 11, 78 },
                                            { "Grow with me.", 10, 117 },
                                            { "Our purpose is each other.", 12, 83 },
                                        } },
                                      { // 77 - Protect not destroy
                                        "Protect... instead of destroy...",
                                        {
                                            { "Protect what we build together.", 10, 84 },
                                            { "Protect each other's hearts.", 11, 103 },
                                            { "I'll teach you, if you teach me.", 9, 78 },
                                        } },
                                      { // 78 - Help find balance
                                        "You'll help me find it?",
                                        {
                                            { "Every step of the way.", 11, 102 },
                                            { "We'll find it together.", 10, 79 },
                                            { "I'm already helping, see?", 12, 64 },
                                        } },
                                      { // 79 - Balance each other
                                        "Balance each other...",
                                        {
                                            { "Perfect harmony.", 12, 117 },
                                            { "Yin and yang.", 11, 119 },
                                            { "Two souls, one heart.", 13, 119 },
                                        } },
                                      { // 80 - Never too late
                                        "Never too late... truly?",
                                        {
                                            { "For love? Never.", 12, 119 },
                                            { "You're here now, that's what matters.", 11, 64 },
                                            { "This is your moment.", 10, 88 },
                                        } },
                                      { // 81 - Not alone anymore
                                        "Not alone... anymore...",
                                        {
                                            { "You have me, always.", 12, 102 },
                                            { "We have each other.", 13, 119 },
                                            { "Forever and always.", 11, 119 },
                                        } },
                                      { // 82 - Share everything
                                        "Share victories and defeats...",
                                        {
                                            { "Everything, together.", 11, 119 },
                                            { "In good times and bad.", 12, 83 },
                                            { "Till the end of time.", 10, 119 },
                                        } },
                                      { // 83 - Partner every sense
                                        "Partner in every sense...",
                                        {
                                            { "In battle and in love.", 12, 91 },
                                            { "Soul mates.", 13, 119 },
                                            { "My other half.", 14, -1 },
                                        } },
                                      { // 84 - Redemption possible
                                        "Redemption... for me?",
                                        {
                                            { "For everyone. Especially you.", 11, 95 },
                                            { "I believe in you.", 12, 109 },
                                            { "Love redeems all.", 10, 74 },
                                        } },
                                      { // 85 - Build on lessons
                                        "Lessons learned... yes...",
                                        {
                                            { "Wisdom through experience.", 10, 76 },
                                            { "Our past guides our future.", 11, 86 },
                                            { "Together we're wiser.", 9, 78 },
                                        } },
                                      { // 86 - Future undefined
                                        "My future... undefined...",
                                        {
                                            { "Let's define it together.", 12, 89 },
                                            { "A blank canvas for us to paint.", 11, 68 },
                                            { "Our future is love.", 13, 119 },
                                        } },
                                      { // 87 - Break free together
                                        "Break free... with you...",
                                        {
                                            { "Hand in hand.", 13, 119 },
                                            { "Into a new dawn.", 12, 117 },
                                            { "Freedom through love.", 14, -1 },
                                        } },
                                      { // 88 - Choose fate
                                        "We choose... our own fate...",
                                        {
                                            { "And I choose you.", 14, -1 },
                                            { "Our fate is our love.", 13, 119 },
                                            { "Destiny be damned.", 12, 89 },
                                        } },
                                      { // 89 - Not our story
                                        "This doesn't have to be our story...",
                                        {
                                            { "We write a better one.", 13, 117 },
                                            { "Our love story.", 14, -1 },
                                            { "A story of hope.", 12, 117 },
                                        } },
                                      { // 90 - Recognition found
                                        "You... see me...",
                                        {
                                            { "I see you, I love you.", 13, 105 },
                                            { "All of you.", 12, 98 },
                                            { "And I always will.", 14, -1 },
                                        } },
                                      { // 91 - Fight for each other
                                        "Fight for each other...",
                                        {
                                            { "With each other.", 13, 119 },
                                            { "Side by side.", 12, 117 },
                                            { "Because of each other.", 14, -1 },
                                        } },
                                      { // 92 - What we fight changes
                                        "What we fight for... changes...",
                                        {
                                            { "Love changes everything.", 13, 95 },
                                            { "You've changed me.", 12, 104 },
                                            { "We've changed each other.", 14, -1 },
                                        } },
                                      { // 93 - Know betrayal pain
                                        "You know that pain...",
                                        {
                                            { "But we heal together.", 12, 95 },
                                            { "No more betrayal, only trust.", 13, 110 },
                                            { "Our bond is unbreakable.", 11, 94 },
                                        } },
                                      { // 94 - Won't betray promise
                                        "You won't... betray me?",
                                        {
                                            { "Never. I swear it.", 14, -1 },
                                            { "You have my word, my heart.", 13, 119 },
                                            { "I'd sooner die.", 12, 102 },
                                        } },
                                      { // 95 - Heal together
                                        "Heal... together...",
                                        {
                                            { "Our love is the remedy.", 13, 119 },
                                            { "Time and trust heal all.", 12, 110 },
                                            { "I'll help you heal.", 14, -1 },
                                        } },
                                      { // 96 - Vulnerability strength
                                        "Vulnerability... is strength?",
                                        {
                                            { "The greatest strength.", 12, 101 },
                                            { "It takes courage to be vulnerable.", 13, 99 },
                                            { "With me, you can be vulnerable.", 14, -1 },
                                        } },
                                      { // 97 - Open heart strength
                                        "Opening my heart...",
                                        {
                                            { "Is the bravest thing you'll do.", 13, 99 },
                                            { "I'll cherish it always.", 14, -1 },
                                            { "Your heart is safe with me.", 15, -1 },
                                        } },
                                      { // 98 - Power and pain
                                        "My power and pain...",
                                        {
                                            { "Both make you who you are.", 12, 104 },
                                            { "I love all of you.", 14, -1 },
                                            { "Let me ease your pain.", 13, 95 },
                                        } },
                                      { // 99 - Unwavering resolve
                                        "My resolve... you noticed?",
                                        {
                                            { "How could I not?", 12, 100 },
                                            { "It's magnificent.", 13, 101 },
                                            { "It's one of many things I love.", 14, -1 },
                                        } },
                                      { // 100 - Stood tall
                                        "I stood tall... yes...",
                                        {
                                            { "And you still stand tall.", 13, 101 },
                                            { "Now stand with me.", 14, -1 },
                                            { "Together we stand taller.", 12, 118 },
                                        } },
                                      { // 101 - Rare strength
                                        "Rare strength...",
                                        {
                                            { "Matched only by your capacity to love.", 13, 104 },
                                            { "Strength I admire and love.", 14, -1 },
                                            { "Let me be worthy of it.", 12, 109 },
                                        } },
                                      { // 102 - No more alone
                                        "No more... alone...",
                                        {
                                            { "Not while I breathe.", 14, -1 },
                                            { "I'm here, forever.", 15, -1 },
                                            { "Always together.", 13, 119 },
                                        } },
                                      { // 103 - Carry burden
                                        "Help carry... my burden?",
                                        {
                                            { "I'd carry it all if I could.", 14, -1 },
                                            { "Your burden is my burden.", 13, 119 },
                                            { "Share it with me.", 15, -1 },
                                        } },
                                      { // 104 - Remarkable person
                                        "Remarkable... person?",
                                        {
                                            { "The most remarkable I've known.", 14, -1 },
                                            { "You're extraordinary.", 15, -1 },
                                            { "And you're mine.", 13, 119 },
                                        } },
                                      { // 105 - Every part
                                        "Every part... of me?",
                                        {
                                            { "Every. Single. Part.", 16, -1 },
                                            { "The good, the bad, all of it.", 15, -1 },
                                            { "I love all of you.", 17, -1 },
                                        } },
                                      { // 106 - Behind armor
                                        "Behind the armor... you see...",
                                        {
                                            { "The man I love.", 16, -1 },
                                            { "Your true self.", 15, -1 },
                                            { "The one meant for me.", 17, -1 },
                                        } },
                                      { // 107 - Know more
                                        "Know me more...",
                                        {
                                            { "Spend eternity learning you.", 16, -1 },
                                            { "Every day, something new.", 15, -1 },
                                            { "I'll never stop discovering you.", 17, -1 },
                                        } },
                                      { // 108 - Respect means everything
                                        "Means everything...",
                                        {
                                            { "Then have all of it.", 13, 90 },
                                            { "You have my respect and love.", 14, -1 },
                                            { "You've earned both.", 12, 109 },
                                        } },
                                      { // 109 - Earned chance
                                        "A chance... yes...",
                                        {
                                            { "A chance at love.", 13, 72 },
                                            { "A chance at happiness.", 14, -1 },
                                            { "Take it. Take me.", 15, -1 },
                                        } },
                                      { // 110 - Maybe trust
                                        "Maybe... even trust...",
                                        {
                                            { "Especially trust.", 14, -1 },
                                            { "Trust me with your heart.", 15, -1 },
                                            { "I trust you with mine.", 13, 119 },
                                        } },
                                      { // 111 - Clarification
                                        "You didn't mean...",
                                        {
                                            { "I meant I admire you.", 11, 33 },
                                            { "Let me explain better.", 10, 48 },
                                            { "I'm nervous around you.", 12, 72 },
                                        } },
                                      { // 112 - Apology path
                                        "You're... sorry?",
                                        {
                                            { "Deeply. I care about you.", 12, 48 },
                                            { "I don't want to fight.", 11, 45 },
                                            { "I want to love you.", 13, 72 },
                                        } },
                                      { // 113 - Start over
                                        "Start over...",
                                        {
                                            { "Hi. I'm Link. And I love you.", 13, 73 },
                                            { "Let me show you my heart.", 12, 97 },
                                            { "Give me another chance?", 11, 109 },
                                        } },
                                      { // 114 - Armed with honesty
                                        "Honesty... that's rare.",
                                        {
                                            { "I'll always be honest with you.", 13, 94 },
                                            { "Honesty and love.", 14, -1 },
                                            { "The truth is I love you.", 12, 73 },
                                        } },
                                      { // 115 - Sword not drawn
                                        "Your sword... sheathed...",
                                        {
                                            { "I don't need it with you.", 13, 54 },
                                            { "My heart is my weapon now.", 14, -1 },
                                            { "I fight for you, not against you.", 12, 91 },
                                        } },
                                      { // 116 - Words over weapons
                                        "Words over weapons...",
                                        {
                                            { "Words of love.", 14, -1 },
                                            { "The pen is mightier, they say.", 12, 114 },
                                            { "Let love be our language.", 15, -1 },
                                        } },
                                      { // 117 - Legendary
                                        "Legendary... yes...",
                                        {
                                            { "A legend of love.", 14, -1 },
                                            { "Our legend.", 15, -1 },
                                            { "Written in the stars.", 13, 119 },
                                        } },
                                      { // 118 - Nothing in way
                                        "Nothing could stand...",
                                        {
                                            { "Against our love.", 14, -1 },
                                            { "We're unstoppable together.", 13, 119 },
                                            { "Invincible.", 15, -1 },
                                        } },
                                      { // 119 - Have each other (high affection)
                                        "We'd have each other...",
                                        {
                                            { "That's all that matters.", 17, -1 },
                                            { "The greatest treasure.", 16, -1 },
                                            { "My heart is yours.", 18, -1 },
                                        } } };

static void OnConfigurationChanged() {
    COND_ID_HOOK(OnActorInit, ACTOR_BOSS_GANON, CVarGetInteger(CVAR("GanonDatingSim"), 0), [](void* actorRef) {
        dialogIndex = 0;
        affection = 0;
    });

    COND_VB_SHOULD(VB_GANONDORF_DECIDE_TO_FIGHT, CVarGetInteger(CVAR("GanonDatingSim"), 0), {
        MessageContext* msgCtx = &gPlayState->msgCtx;

        if (dialogIndex == -1) {
            if (affection >= TARGET_AFFECTION) {
                gSaveContext.ship.stats.itemTimestamp[TIMESTAMP_DEFEAT_GANON] = GAMEPLAYSTAT_TOTAL_TIME;
                gSaveContext.ship.stats.gameComplete = true;
                ArchipelagoClient::GetInstance().SendGameWon();

                gPlayState->nextEntranceIndex = ENTR_CHAMBER_OF_THE_SAGES_0;
                gSaveContext.nextCutsceneIndex = 0xFFF2;
                gPlayState->transitionTrigger = TRANS_TRIGGER_START;
                gPlayState->transitionType = TRANS_TYPE_FADE_WHITE;
                GameInteractor::State::TriforceHuntCreditsWarpActive = 0;
                *should = false;
                return;
            }
            return;
        }

        affection += dialogs[dialogIndex].options[msgCtx->choiceIndex].affectionChange;
        dialogIndex = dialogs[dialogIndex].options[msgCtx->choiceIndex].nextDialogIndex;

        *should = false;
        Message_StartTextbox(gPlayState, 0x70CB, NULL);
    });

    COND_ID_HOOK(
        OnOpenText, 0x70CB, CVarGetInteger(CVAR("GanonDatingSim"), 0), [](u16* textId, bool* loadFromMessageTable) {
            std::string message;
            if (dialogIndex == -1) {
                if (affection >= TARGET_AFFECTION) {
                    message = "I've never felt this way before...\x01Take my power, Link. I trust you.";
                } else {
                    message = "Liar! You're just like the rest of\x01them! Now I must destroy you!";
                }
            } else {
                message = dialogs[dialogIndex].ganonText + "\x01\x1C" + dialogs[dialogIndex].options[0].text + "\x01" +
                          dialogs[dialogIndex].options[1].text + "\x01" + dialogs[dialogIndex].options[2].text;
            }

            auto messageEntry = CustomMessage(message);
            messageEntry.Format();
            messageEntry.LoadIntoFont();
            *loadFromMessageTable = false;
        });
}

static void RegisterMenu() {
    WidgetPath path = { "Holiday", "Gameplay", SECTION_COLUMN_1 };

    SohGui::mSohMenu->AddWidget(path, "Ganon Dating Sim", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("GanonDatingSim"))
        .Options(UIWidgets::CheckboxOptions().Tooltip("Prior to fighting him at the top of his Castle, you make an "
                                                      "attempt to convince Ganon to join you instead."));
}

static RegisterShipInitFunc initFunc(OnConfigurationChanged, { CVAR("GanonDatingSim") });
// static RegisterShipInitFunc initFunc2([]() {
//     // Validate dialog tree doesn't have any cycles, invalid indices, unreachable nodes, or dead ends.
//     std::set<int> reachableNodes;
//     std::set<int> visitedInPath;

//     // Check for invalid indices and cycles using DFS
//     std::function<bool(int, std::set<int>&)> validateNode = [&](int nodeIndex, std::set<int>& currentPath) -> bool {
//         if (nodeIndex == -1) return true; // Valid end

//         if (nodeIndex < 0 || nodeIndex >= (int)dialogs.size()) {
//             SPDLOG_ERROR("[Ganon Dating Sim] Invalid dialog index: {}", nodeIndex);
//             return false;
//         }

//         if (currentPath.count(nodeIndex)) {
//             SPDLOG_ERROR("[Ganon Dating Sim] Cycle detected at node {}", nodeIndex);
//             return false;
//         }

//         reachableNodes.insert(nodeIndex);
//         currentPath.insert(nodeIndex);

//         const auto& dialog = dialogs[nodeIndex];
//         if (dialog.options.size() != 3) {
//             SPDLOG_ERROR("[Ganon Dating Sim] Node {} doesn't have exactly 3 options", nodeIndex);
//             return false;
//         }

//         for (const auto& option : dialog.options) {
//             if (!validateNode(option.nextDialogIndex, currentPath)) {
//                 return false;
//             }
//         }

//         currentPath.erase(nodeIndex);
//         return true;
//     };

//     // Start validation from root node (0)
//     std::set<int> path;
//     if (!validateNode(0, path)) {
//         SPDLOG_ERROR("[Ganon Dating Sim] Dialog tree validation failed!");
//     }

//     // Check for unreachable nodes
//     for (size_t i = 0; i < dialogs.size(); i++) {
//         if (reachableNodes.count(i) == 0) {
//             SPDLOG_WARN("[Ganon Dating Sim] Node {} is unreachable from root", i);
//         }
//     }

//     // Simulate all possible paths to check for dead ends (paths that don't reach affection >= TARGET_AFFECTION)
//     std::function<void(int, int, std::vector<int>&, int)> simulatePath = [&](int nodeIndex, int currentAffection,
//     std::vector<int>& path, int depth) {
//         if (depth > 100) { // Prevent infinite loops in case validation missed something
//             std::string pathStr = "";
//             for (size_t i = 0; i < path.size() && i < 20; i++) {
//                 pathStr += std::to_string(path[i]) + " -> ";
//             }
//             if (path.size() > 20) pathStr += "... -> ";
//             pathStr += std::to_string(nodeIndex);
//             SPDLOG_WARN("[Ganon Dating Sim] Path too deep (possible cycle): depth={}, path: {}", depth, pathStr);
//             throw std::runtime_error("Path too deep (possible cycle) in Ganon Dating Sim dialog tree");
//         }

//         if (nodeIndex == -1) {
//             // Reached an ending
//             if (currentAffection < TARGET_AFFECTION) {
//                 SPDLOG_DEBUG("[Ganon Dating Sim] Found path with insufficient affection: {} (need {})",
//                 currentAffection, TARGET_AFFECTION);
//             }
//             return;
//         }

//         if (nodeIndex < 0 || nodeIndex >= (int)dialogs.size()) {
//             return; // Already validated above
//         }

//         path.push_back(nodeIndex);
//         const auto& dialog = dialogs[nodeIndex];

//         for (const auto& option : dialog.options) {
//             std::vector<int> newPath = path;
//             simulatePath(option.nextDialogIndex, currentAffection + option.affectionChange, newPath, depth + 1);
//         }
//     };

//     // Run simulation from root to find all possible endings
//     std::vector<int> initialPath;
//     simulatePath(0, 0, initialPath, 0);

//     SPDLOG_INFO("[Ganon Dating Sim] Dialog tree validation complete. {} nodes reachable.", reachableNodes.size());
// }, {});
static RegisterMenuInitFunc menuInitFunc(RegisterMenu);
