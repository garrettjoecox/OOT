#include "Caladius.h"
#include "Holiday.hpp"
#include "soh/Notification/Notification.h"
#include "soh/Enhancements/gameplaystats.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/custom-message/CustomMessageManager.h"
#include "soh/Enhancements/randomizer/randomizer.h"
#include "soh/frame_interpolation.h"
#include "soh/ObjectExtension/ActorListIndex.h"
#include "soh_assets.h"

extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
extern PlayState* gPlayState;
uint64_t GetUnixTimestamp();
}

#define CVAR(v) "gHoliday.Gameplay." v

bool isFeverDisabled = false;
bool isExchangeDisabled = false;
static float fontScale = 1.0f;

extern GetItemEntry vanillaQueuedItemEntry;

std::vector<ActorID> boulderList = { ACTOR_OBJ_BOMBIWA, ACTOR_BG_ICE_SHELTER, ACTOR_EN_ISHI, ACTOR_EN_ISHI,
                                     ACTOR_OBJ_HAMISHI };

std::string formatTimestampIceTrapFever(uint32_t value) {
    uint32_t sec = value / 10;
    uint32_t hh = sec / 3600;
    uint32_t mm = (sec - hh * 3600) / 60;
    uint32_t ss = sec - hh * 3600 - mm * 60;
    return fmt::format("{}:{:0>2}:{:0>2}", hh, mm, ss);
}

void OnTimeOver() {
    gSaveContext.health = 0;
}

int32_t calculateRemainingTime() {
    int32_t timeRemaining =
        ((gSaveContext.ship.stats.count[COUNT_ICE_TRAPS] * (CVarGetInteger(CVAR("ExtendTimer"), 0) * 600)) +
         (CVarGetInteger(CVAR("StartTimer"), 0) * 600) - GAMEPLAYSTAT_TOTAL_TIME);
    if (timeRemaining <= 0) {
        OnTimeOver();
        timeRemaining = 0;
    }
    return timeRemaining;
}

s32 ActorSnapToFloor(Actor* refActor, PlayState* play, f32 arg2) {
    CollisionPoly* poly;
    Vec3f pos;
    s32 bgId;
    f32 floorY;

    pos.x = refActor->world.pos.x;
    pos.y = refActor->world.pos.y + 30.0f;
    pos.z = refActor->world.pos.z;
    floorY = BgCheck_EntityRaycastFloor4(&play->colCtx, &poly, &bgId, refActor, &pos);
    if (floorY > BGCHECK_Y_MIN) {
        refActor->world.pos.y = floorY + arg2;
        Math_Vec3f_Copy(&refActor->home.pos, &refActor->world.pos);
    }
    return refActor->world.pos.y;
}

void RandomizeBoulder(Actor* refActor) {
    Actor* actor = (Actor*)refActor;
    int16_t param = 0;
    int32_t yAdj = 0;

    int32_t seed = gPlayState->sceneNum + actor->id + ((int32_t)(actor->world.pos.x * 10)) +
                   ((int32_t)(actor->world.pos.y * 10)) + ((int32_t)(actor->world.pos.z * 10)) + actor->params;

    uint32_t finalSeed =
        ABS(seed) + (IS_RANDO ? Rando::Context::GetInstance()->GetSeed() : gSaveContext.ship.stats.fileCreatedAt);
    Random_Init(finalSeed);
    uint32_t roll = Random(0, boulderList.size());

    u32 flag = actor->id == ACTOR_EN_ISHI ? ((actor->params >> 0xA) & 0x3C) | ((actor->params >> 6) & 3)
                                          : actor->params & 0x3F;

    if (boulderList[roll] == ACTOR_EN_ISHI) {
        param = (Random(0, 2)) | ((flag & 0x3C) << 10) | ((flag & 3) << 6);
    } else {
        param = flag;
    }

    yAdj = ActorSnapToFloor(actor, gPlayState, 0.0f);

    Actor_Spawn(&gPlayState->actorCtx, gPlayState, boulderList[roll], actor->world.pos.x,
                ActorSnapToFloor(actor, gPlayState, 0.0f), actor->world.pos.z, 0, 0, 0, param, false);
}

bool spawningPresents = false;

struct Present {};

std::unordered_map<Actor*, Present> presents;

void Present_Init(Actor* actor, PlayState* play) {
    Present present;
    presents[actor] = present;

    actor->gravity = -1;
    Actor_MoveXZGravity(actor);
    actor->shape.rot.y = Random(0, 0xFFFF);

    Actor_UpdateBgCheckInfo(play, actor, 10.0f, 10.0f, 0.0f, 0xFF);
}

void Present_Update(Actor* actor, PlayState* play) {
    Present* present = &presents[actor];

    if (actor->xzDistToPlayer < 50.0f && actor->yDistToPlayer < 50.0f) {
        uint32_t giftsCollected = CVarGetInteger(CVAR("GiftsCollected"), 0);
        giftsCollected++;
        CVarSetInteger(CVAR("GiftsCollected"), giftsCollected);
        Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesNextFrame();
        std::string msg = std::to_string(giftsCollected).c_str();
        msg += " Gifts in Inventory.";
        Notification::Emit({
            .itemIcon = "RG_TRIFORCE_PIECE",
            .message = msg,
            .messageColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
        });
        Actor_Kill(actor);
    }
}

void Present_Draw(Actor* actor, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    Matrix_Scale(30.0f, 30.0f, 30.0f, MTXMODE_APPLY);
    Matrix_Translate(49.20f, 0.0f, -106.60f, MTXMODE_APPLY);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx, (char*)__FILE__, __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
    gSPDisplayList(POLY_OPA_DISP++, (Gfx*)gXmasDecor100DL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void Present_Destroy(Actor* actor, PlayState* play) {
    presents.erase(actor);
}

static void OnPresentChange() {
    isExchangeDisabled = !CVarGetInteger(CVAR("OrnExch.Enabled"), 0);
    COND_ID_HOOK(
        OnOpenText, 0x204A, CVarGetInteger(CVAR("OrnExch.Enabled"), 0), [](u16* textId, bool* loadFromMessageTable) {
            auto messageEntry = CustomMessage("");
            bool reduceGifts = false;
            uint32_t giftsCollected = CVarGetInteger(CVAR("GiftsCollected"), 0);
            uint32_t giftsRequired = CVarGetInteger(CVAR("OrnExch.Amount"), 15);
            if (giftsCollected < giftsRequired) {
                std::string msg = "You only have %r " + std::to_string(giftsCollected) + "%w If you bring me %g" +
                                  std::to_string(giftsRequired) + "%w I'll give you a reward!";
                messageEntry = CustomMessage(msg);
            } else {
                std::string msg = "A present? And %g" + std::to_string(giftsRequired) +
                                  "%w to boot? Here's your reward, bring me more if you find any!";
                messageEntry = CustomMessage(msg);
                reduceGifts = true;
            }
            messageEntry.AutoFormat();
            messageEntry.LoadIntoFont();
            *loadFromMessageTable = false;

            if (reduceGifts) {
                vanillaQueuedItemEntry = Rando::StaticData::RetrieveItem(RG_TRIFORCE_PIECE).GetGIEntry_Copy();
                giftsCollected -= giftsRequired;
                CVarSetInteger(CVAR("GiftsCollected"), giftsCollected);
                Ship::Context::GetInstance()->GetWindow()->GetGui()->SaveConsoleVariablesNextFrame();

                std::string msg = std::to_string(giftsCollected).c_str();
                msg += " Gifts in Inventory.";
                Notification::Emit({ .itemIcon = "RG_TRIFORCE_PIECE", .message = msg });
            }
        });

    COND_HOOK(OnSceneSpawnActors, CVarGetInteger(CVAR("OrnExch.Enabled"), 0), []() {
        presents.clear();
        Vec3f pos;
        static CollisionPoly presentPoly;
        static f32 raycastResult;
        pos.y = 9999.0f;
        int spawnAttempts = 0;
        while (spawnAttempts < 20) {
            if (GET_PLAYER(gPlayState) != nullptr) {
                pos.x = GET_PLAYER(gPlayState)->actor.world.pos.x;
                pos.z = GET_PLAYER(gPlayState)->actor.world.pos.z;
            } else {
                pos.x = 0;
                pos.z = 0;
            }
            // X/Z anywhere from -1000.0 to +1000.0 from player
            pos.x += (float)(Random(0, 20000)) - 10000.0f;
            pos.z += (float)(Random(0, 20000)) - 10000.0f;

            raycastResult = BgCheck_AnyRaycastFloor1(&gPlayState->colCtx, &presentPoly, &pos);

            if (raycastResult > BGCHECK_Y_MIN) {
                spawningPresents = true;
                Actor* actor = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_OE2, pos.x, raycastResult, pos.z,
                                           0, 0, 0, 0, false);
                spawningPresents = false;
                // break;
            }

            spawnAttempts++;
        }
    });

    COND_ID_HOOK(ShouldActorInit, ACTOR_EN_OE2, CVarGetInteger(CVAR("OrnExch.Enabled"), 0),
                 [](void* actorRef, bool* should) {
                     Actor* actor = (Actor*)actorRef;
                     if (spawningPresents) {
                         actor->init = Present_Init;
                         actor->update = Present_Update;
                         actor->draw = Present_Draw;
                         actor->destroy = Present_Destroy;
                     }
                 });
}

static bool isRandomizingBoulder = false;
static void OnBlitzChange() {
    COND_HOOK(ShouldActorInit, CVarGetInteger(CVAR("Blitz.Enabled"), 0), [](void* actorRef, bool* should) {
        if (isRandomizingBoulder)
            return;

        Actor* actor = (Actor*)actorRef;
        for (auto& boulderActor : boulderList) {
            if (actor->id == boulderActor) {
                isRandomizingBoulder = true;
                RandomizeBoulder(actor);
                isRandomizingBoulder = false;
                *should = false;
                return;
            }
        }
    });
}

static void OnFeverConfigurationChanged() {
    isFeverDisabled = !CVarGetInteger(CVAR("Fever.Enabled"), 0);
    fontScale = CVarGetFloat(CVAR("FontScale"), 1.0f);
    if (fontScale < 1.0f) {
        fontScale = 1.0f;
    }
}

void CaladiusWindow::Draw() {
    if (!CVarGetInteger(CVAR("Fever.Enabled"), 0)) {
        return;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
    ImGui::Begin("TimerDisplay", nullptr,
                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing |
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetWindowFontScale(fontScale);
    ImGui::Text(formatTimestampIceTrapFever(calculateRemainingTime()).c_str());
    ImGui::End();

    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(1);
}

static void RegisterMenu() {
    WidgetPath path = { "Holiday", "Gameplay", SECTION_COLUMN_2 };
    SohGui::mSohMenu->AddWidget(path, "Holiday Fever", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("Fever.Enabled"))
        .Callback([](WidgetInfo& info) { OnFeverConfigurationChanged(); })
        .Options(UIWidgets::CheckboxOptions().Tooltip(
            "Death will come for you when the timer runs out? Obtaining Ice Traps extends your timer. \n\nShould be "
            "enabled before starting a new file, won't work well with existing files."));
    SohGui::mSohMenu->AddWidget(path, "Starting Timer: %d minutes", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR("StartTimer"))
        .Callback([](WidgetInfo& info) { OnFeverConfigurationChanged(); })
        .PreFunc([](WidgetInfo& info) { info.options.get()->disabled = !CVarGetInteger(CVAR("Fever.Enabled"), 0); })
        .Options(UIWidgets::IntSliderOptions().DefaultValue(15).Min(5).Max(30));
    SohGui::mSohMenu->AddWidget(path, "Time Extensions: %d minutes", WIDGET_CVAR_SLIDER_INT)
        .CVar(CVAR("ExtendTimer"))
        .Callback([](WidgetInfo& info) { OnFeverConfigurationChanged(); })
        .PreFunc([](WidgetInfo& info) { info.options.get()->disabled = !CVarGetInteger(CVAR("Fever.Enabled"), 0); })
        .Options(UIWidgets::IntSliderOptions().DefaultValue(5).Min(1).Max(10));

    path.column = SECTION_COLUMN_1;

    SohGui::mSohMenu->AddWidget(path, "Shuffle Boulders & Ice", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("Blitz.Enabled"))
        .Callback([](WidgetInfo& info) { OnBlitzChange(); })
        .Options(UIWidgets::CheckboxOptions().Tooltip(
            "Boulders & Ice will randomly be replaced with other boulders & ice when the scene loads."));
}

static void RegisterMod() {
    OnFeverConfigurationChanged();
    OnBlitzChange();
    OnPresentChange();
}

static RegisterShipInitFunc initFunc(RegisterMod);
static RegisterMenuInitFunc menuInitFunc(RegisterMenu);
