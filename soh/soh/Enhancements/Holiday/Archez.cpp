#include "Holiday.hpp"
#include "Archez.h"
#include <libultraship/libultraship.h>
#include "soh/SohGui/UIWidgets.hpp"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh_assets.h"

extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
#include "objects/object_goroiwa/object_goroiwa.h"

extern PlayState* gPlayState;
}

#define CVAR(v) "gHoliday.Gameplay." v

static bool sSkipNextLimb = false;
static bool sSkipNextSkeleton = false;

extern "C" void SkipOverrideNextLimb() {
    sSkipNextLimb = true;
}

extern "C" void SkipOverrideNextSkeleton() {
    sSkipNextSkeleton = true;
}

extern "C" void ClearOverrideSkips() {
    sSkipNextLimb = false;
    sSkipNextSkeleton = false;
}

static void OnConfigurationChanged() {
    COND_VB_SHOULD(VB_DRAW_SKEL_LIMB, CVarGetInteger(CVAR("SnowGolems"), 0), {
        if (!*should) {
            return;
        }

        if (sSkipNextLimb) {
            sSkipNextLimb = false;
            return;
        }

        if (sSkipNextSkeleton) {
            return;
        }

        Gfx** gfxP = va_arg(args, Gfx**);
        void* dList = va_arg(args, void*);

        *should = false;

        Gfx* gfx = *gfxP;

        Matrix_Push();

        Matrix_Scale(0.55f, 0.55f, 0.55f, MTXMODE_APPLY);
        gSPMatrix(gfx++, Matrix_NewMtx(gPlayState->state.gfxCtx, (char*)__FILE__, __LINE__), G_MTX_LOAD);
        gSPDisplayList(gfx++, (Gfx*)gSnowballDL);

        Matrix_Pop();

        gSPMatrix(gfx++, Matrix_NewMtx(gPlayState->state.gfxCtx, (char*)__FILE__, __LINE__), G_MTX_LOAD);

        *gfxP = gfx;
    });

    COND_VB_SHOULD(VB_DRAW_SKEL_FLEX_LIMB, CVarGetInteger(CVAR("SnowGolems"), 0), {
        if (!*should) {
            return;
        }

        if (sSkipNextLimb) {
            sSkipNextLimb = false;
        }

        if (sSkipNextSkeleton) {
            return;
        }

        Gfx** gfxP = va_arg(args, Gfx**);
        void* dList = va_arg(args, void*);
        Mtx* mtx = va_arg(args, Mtx*);

        *should = false;

        Gfx* gfx = *gfxP;
        MtxF mtxF;

        Matrix_Push();
        Matrix_MtxToMtxF(mtx, &mtxF);
        Matrix_Put(&mtxF);

        Matrix_Scale(0.55f, 0.55f, 0.55f, MTXMODE_APPLY);
        gSPMatrix(gfx++, Matrix_NewMtx(gPlayState->state.gfxCtx, (char*)__FILE__, __LINE__), G_MTX_LOAD);
        gSPDisplayList(gfx++, (Gfx*)gSnowballDL);

        Matrix_Pop();

        gSPMatrix(gfx++, mtx, G_MTX_LOAD);

        *gfxP = gfx;
    });
}

static void RegisterMenu() {
    WidgetPath path = { "Holiday", "Visual", SECTION_COLUMN_1 };
    SohGui::mSohMenu->AddWidget(path, "Snow Golems", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("SnowGolems"))
        .Callback([](WidgetInfo& info) { OnConfigurationChanged(); })
        .Options(UIWidgets::CheckboxOptions().Tooltip(
            "Overrides most charactor skeletons with snow balls to make them look like Snow Golems"));
}

static RegisterShipInitFunc initFunc(OnConfigurationChanged, { CVAR("SnowGolems") });
static RegisterMenuInitFunc menuInitFunc(RegisterMenu);
