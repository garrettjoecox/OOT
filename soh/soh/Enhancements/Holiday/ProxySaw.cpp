#include "Holiday.hpp"
#include <libultraship/libultraship.h>
#include "soh/SohGui/UIWidgets.hpp"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "objects/object_dog/object_dog.h"
#include "soh/frame_interpolation.h"
#include "soh/Enhancements/randomizer/3drando/random.hpp"
#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"
#include <set>

#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/object_md/object_md.h"
#include "src/overlays/actors/ovl_Door_Ana/z_door_ana.h"
extern "C" {
#include "macros.h"
#include "functions.h"
#include "variables.h"
#include "objects/object_wood02/object_wood02.h"
#include "scenes/overworld/spot00/spot00_room_0.h"
#include "scenes/overworld/spot04/spot04_room_0.h"
#include "scenes/overworld/spot04/spot04_room_1.h"
#include "scenes/overworld/spot20/spot20_room_0.h"
#include "scenes/overworld/spot03/spot03_room_0.h"
#include "scenes/overworld/spot15/spot15_room_0.h"

void ResourceMgr_PatchGfxByName(const char* path, const char* patchName, int index, Gfx instruction);
void ResourceMgr_UnpatchGfxByName(const char* path, const char* patchName);

extern PlayState* gPlayState;
extern "C" s16 gEnSnowballId;
void DoorAna_SetupAction(DoorAna* doorAna, DoorAnaActionFunc actionFunc);
void DoorAna_GrabPlayer(DoorAna* doorAna, PlayState* play);
}

#define CVAR(v) "gHoliday.Gameplay." v

static CollisionPoly snowballPoly;
static Vec3f snowballPos;
static f32 raycastResult;

static u32 iceBlockParams[] = {
    0x214, 0x1, 0x11, 0x10, 0x20,
};

static void SpawnSnowballs() {
    if (gPlayState->sceneNum != SCENE_HYRULE_FIELD && gPlayState->sceneNum != SCENE_KAKARIKO_VILLAGE) {
        return;
    }

    int actorsSpawned = 0;

    while (actorsSpawned < 30) {
        snowballPos.x = (float)(Random((gPlayState->sceneNum == SCENE_HYRULE_FIELD ? -10000 : -2700) + 10000,
                                       (gPlayState->sceneNum == SCENE_HYRULE_FIELD ? 5000 : 2000) + 10000) -
                                (float)10000.0f);
        snowballPos.y = 5000;
        snowballPos.z = (float)(Random((gPlayState->sceneNum == SCENE_HYRULE_FIELD ? -1000 : -2000) + 10000,
                                       (gPlayState->sceneNum == SCENE_HYRULE_FIELD ? 15000 : 2000) + 10000) -
                                (float)10000.0f);

        raycastResult = BgCheck_AnyRaycastFloor1(&gPlayState->colCtx, &snowballPoly, &snowballPos);

        if (raycastResult > BGCHECK_Y_MIN) {
            Actor_Spawn(&gPlayState->actorCtx, gPlayState, gEnSnowballId, snowballPos.x, raycastResult, snowballPos.z,
                        0, 0, 0, gPlayState->sceneNum == SCENE_HYRULE_FIELD, 0);
            actorsSpawned++;
        }
    }
}

static void SpawnIcebergs() {
    if (gPlayState->sceneNum != SCENE_LAKE_HYLIA) {
        return;
    }

    int actorsSpawned = 0;

    Vec3f spawnedIceBlockPos[15];

    while (actorsSpawned < 15) {
        Vec3f iceBlockPos;
        iceBlockPos.x = (float)(Random((-4200) + 10000, (3000) + 10000) - (float)10000.0f);
        iceBlockPos.y = -1713.0f;
        iceBlockPos.z = (float)(Random((2600) + 10000, (9000) + 10000) - (float)10000.0f);

        raycastResult = BgCheck_AnyRaycastFloor1(&gPlayState->colCtx, &snowballPoly, &iceBlockPos);

        if (raycastResult > BGCHECK_Y_MIN) {

            bool overlaps = false;
            for (int i = 0; i < actorsSpawned; i++) {
                if (Math_Vec3f_DistXZ(&spawnedIceBlockPos[i], &iceBlockPos) < 500.0f) {
                    overlaps = true;
                    break;
                }
            }

            if (overlaps) {
                continue;
            }

            if (LINK_IS_ADULT && !Flags_GetEventChkInf(EVENTCHKINF_RAISED_LAKE_HYLIA_WATER)) {
                iceBlockPos.y = raycastResult;
            } else {
                iceBlockPos.y = -1310.0f;
            }

            Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_BG_SPOT08_ICEBLOCK, iceBlockPos.x, iceBlockPos.y,
                        iceBlockPos.z, 0, (s16)Random(0, 0xFFFF), 0, RandomElement(iceBlockParams), 0);
            spawnedIceBlockPos[actorsSpawned] = iceBlockPos;
            actorsSpawned++;
        }
    }
}

std::vector<uint32_t> validEntrances = {
    ENTR_DEKU_TREE_ENTRANCE,
    ENTR_KOKIRI_FOREST_OUTSIDE_DEKU_TREE,
    ENTR_DODONGOS_CAVERN_ENTRANCE,
    ENTR_DEATH_MOUNTAIN_TRAIL_OUTSIDE_DODONGOS_CAVERN,
    ENTR_JABU_JABU_ENTRANCE,
    ENTR_ZORAS_FOUNTAIN_OUTSIDE_JABU_JABU,
    ENTR_FOREST_TEMPLE_ENTRANCE,
    ENTR_SACRED_FOREST_MEADOW_OUTSIDE_TEMPLE,
    ENTR_FIRE_TEMPLE_ENTRANCE,
    ENTR_DEATH_MOUNTAIN_CRATER_OUTSIDE_TEMPLE,
    ENTR_WATER_TEMPLE_ENTRANCE,
    ENTR_LAKE_HYLIA_OUTSIDE_TEMPLE,
    ENTR_SPIRIT_TEMPLE_ENTRANCE,
    ENTR_DESERT_COLOSSUS_OUTSIDE_TEMPLE,
    ENTR_SHADOW_TEMPLE_ENTRANCE,
    ENTR_GRAVEYARD_OUTSIDE_TEMPLE,
    ENTR_BOTTOM_OF_THE_WELL_ENTRANCE,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_BOTTOM_OF_THE_WELL,
    ENTR_ICE_CAVERN_ENTRANCE,
    ENTR_ZORAS_FOUNTAIN_OUTSIDE_ICE_CAVERN,
    ENTR_GERUDO_TRAINING_GROUND_ENTRANCE,
    ENTR_GERUDOS_FORTRESS_OUTSIDE_GERUDO_TRAINING_GROUND,
    ENTR_INSIDE_GANONS_CASTLE_ENTRANCE,
    ENTR_CASTLE_GROUNDS_RAINBOW_BRIDGE_EXIT,
    ENTR_MIDOS_HOUSE_0,
    ENTR_KOKIRI_FOREST_OUTSIDE_MIDOS_HOUSE,
    ENTR_SARIAS_HOUSE_0,
    ENTR_KOKIRI_FOREST_OUTSIDE_SARIAS_HOUSE,
    ENTR_TWINS_HOUSE_0,
    ENTR_KOKIRI_FOREST_OUTSIDE_TWINS_HOUSE,
    ENTR_KNOW_IT_ALL_BROS_HOUSE_0,
    ENTR_KOKIRI_FOREST_OUTSIDE_KNOW_IT_ALL_HOUSE,
    ENTR_KOKIRI_SHOP_0,
    ENTR_KOKIRI_FOREST_OUTSIDE_SHOP,
    ENTR_LAKESIDE_LABORATORY_0,
    ENTR_LAKE_HYLIA_OUTSIDE_LAB,
    ENTR_FISHING_POND_0,
    ENTR_LAKE_HYLIA_OUTSIDE_FISHING_POND,
    ENTR_CARPENTERS_TENT_0,
    ENTR_GERUDO_VALLEY_OUTSIDE_TENT,
    ENTR_MARKET_GUARD_HOUSE_0,
    ENTR_MARKET_ENTRANCE_OUTSIDE_GUARD_HOUSE,
    ENTR_HAPPY_MASK_SHOP_0,
    ENTR_MARKET_DAY_OUTSIDE_HAPPY_MASK_SHOP,
    ENTR_BOMBCHU_BOWLING_ALLEY_0,
    ENTR_MARKET_DAY_OUTSIDE_BOMBCHU_BOWLING,
    ENTR_POTION_SHOP_MARKET_0,
    ENTR_MARKET_DAY_OUTSIDE_POTION_SHOP,
    ENTR_TREASURE_BOX_SHOP_0,
    ENTR_MARKET_DAY_OUTSIDE_TREASURE_BOX_SHOP,
    ENTR_BOMBCHU_SHOP_1,
    ENTR_BACK_ALLEY_DAY_OUTSIDE_BOMBCHU_SHOP,
    ENTR_BACK_ALLEY_MAN_IN_GREEN_HOUSE,
    ENTR_BACK_ALLEY_DAY_OUTSIDE_MAN_IN_GREEN_HOUSE,
    ENTR_KAKARIKO_CENTER_GUEST_HOUSE_0,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_CENTER_GUEST_HOUSE,
    ENTR_HOUSE_OF_SKULLTULA_0,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_SKULKLTULA_HOUSE,
    ENTR_IMPAS_HOUSE_FRONT,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_IMPAS_HOUSE_FRONT,
    ENTR_IMPAS_HOUSE_BACK,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_IMPAS_HOUSE_BACK,
    ENTR_POTION_SHOP_GRANNY_0,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_SHOP_GRANNY,
    ENTR_GRAVEKEEPERS_HUT_0,
    ENTR_GRAVEYARD_OUTSIDE_DAMPES_HUT,
    ENTR_GORON_SHOP_0,
    ENTR_GORON_CITY_OUTSIDE_SHOP,
    ENTR_ZORA_SHOP_0,
    ENTR_ZORAS_DOMAIN_OUTSIDE_SHOP,
    ENTR_LON_LON_BUILDINGS_TALONS_HOUSE,
    ENTR_LON_LON_RANCH_OUTSIDE_TALONS_HOUSE,
    ENTR_STABLE_0,
    ENTR_LON_LON_RANCH_OUTSIDE_STABLES,
    ENTR_LON_LON_BUILDINGS_TOWER,
    ENTR_LON_LON_RANCH_OUTSIDE_TOWER,
    ENTR_BAZAAR_1,
    ENTR_MARKET_DAY_OUTSIDE_BAZAAR,
    ENTR_SHOOTING_GALLERY_1,
    ENTR_MARKET_DAY_OUTSIDE_SHOOTING_GALLERY,
    ENTR_BAZAAR_0,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_BAZAAR,
    ENTR_SHOOTING_GALLERY_0,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_SHOOTING_GALLERY,
    ENTR_GREAT_FAIRYS_FOUNTAIN_SPELLS_NAYRUS_COLOSSUS,
    ENTR_DESERT_COLOSSUS_GREAT_FAIRY_EXIT,
    ENTR_GREAT_FAIRYS_FOUNTAIN_SPELLS_DINS_HC,
    ENTR_CASTLE_GROUNDS_GREAT_FAIRY_EXIT,
    ENTR_GREAT_FAIRYS_FOUNTAIN_MAGIC_OGC_DD,
    ENTR_POTION_SHOP_KAKARIKO_1,
    ENTR_GREAT_FAIRYS_FOUNTAIN_MAGIC_DMC,
    ENTR_DEATH_MOUNTAIN_CRATER_GREAT_FAIRY_EXIT,
    ENTR_GREAT_FAIRYS_FOUNTAIN_MAGIC_DMT,
    ENTR_DEATH_MOUNTAIN_TRAIL_GREAT_FAIRY_EXIT,
    ENTR_GREAT_FAIRYS_FOUNTAIN_SPELLS_FARORES_ZF,
    ENTR_ZORAS_FOUNTAIN_OUTSIDE_GREAT_FAIRY,
    ENTR_LINKS_HOUSE_1,
    ENTR_KOKIRI_FOREST_OUTSIDE_LINKS_HOUSE,
    ENTR_TEMPLE_OF_TIME_ENTRANCE,
    ENTR_TEMPLE_OF_TIME_EXTERIOR_DAY_OUTSIDE_TEMPLE,
    ENTR_WINDMILL_AND_DAMPES_GRAVE_WINDMILL,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_WINDMILL,
    ENTR_POTION_SHOP_KAKARIKO_FRONT,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_POTION_SHOP_FRONT,
    ENTR_POTION_SHOP_KAKARIKO_BACK,
    ENTR_KAKARIKO_VILLAGE_OUTSIDE_POTION_SHOP_BACK,
    ENTR_GRAVE_WITH_FAIRYS_FOUNTAIN_0,
    ENTR_GRAVEYARD_SHIELD_GRAVE_EXIT,
    ENTR_REDEAD_GRAVE_0,
    ENTR_GRAVEYARD_HEART_PIECE_GRAVE_EXIT,
    ENTR_ROYAL_FAMILYS_TOMB_0,
    ENTR_GRAVEYARD_ROYAL_TOMB_EXIT,
    ENTR_WINDMILL_AND_DAMPES_GRAVE_GRAVE,
    ENTR_GRAVEYARD_DAMPES_GRAVE_EXIT,
    ENTR_LOST_WOODS_BRIDGE_EAST_EXIT,
    ENTR_KOKIRI_FOREST_LOWER_EXIT,
    ENTR_LOST_WOODS_SOUTH_EXIT,
    ENTR_KOKIRI_FOREST_UPPER_EXIT,
    ENTR_GORON_CITY_TUNNEL_SHORTCUT,
    ENTR_LOST_WOODS_TUNNEL_SHORTCUT,
    ENTR_ZORAS_RIVER_UNDERWATER_SHORTCUT,
    ENTR_LOST_WOODS_UNDERWATER_SHORTCUT,
    ENTR_SACRED_FOREST_MEADOW_SOUTH_EXIT,
    ENTR_LOST_WOODS_NORTH_EXIT,
    ENTR_HYRULE_FIELD_WOODED_EXIT,
    ENTR_LOST_WOODS_BRIDGE_WEST_EXIT,
    ENTR_LAKE_HYLIA_NORTH_EXIT,
    ENTR_HYRULE_FIELD_FENCE_EXIT,
    ENTR_GERUDO_VALLEY_EAST_EXIT,
    ENTR_HYRULE_FIELD_ROCKY_PATH,
    ENTR_MARKET_ENTRANCE_NEAR_GUARD_EXIT,
    ENTR_HYRULE_FIELD_ON_BRIDGE_SPAWN,
    ENTR_KAKARIKO_VILLAGE_FRONT_GATE,
    ENTR_HYRULE_FIELD_STAIRS_EXIT,
    ENTR_ZORAS_RIVER_WEST_EXIT,
    ENTR_HYRULE_FIELD_RIVER_EXIT,
    ENTR_LON_LON_RANCH_ENTRANCE,
    ENTR_HYRULE_FIELD_CENTER_EXIT,
    ENTR_ZORAS_DOMAIN_UNDERWATER_SHORTCUT,
    ENTR_LAKE_HYLIA_UNDERWATER_SHORTCUT,
    ENTR_GERUDOS_FORTRESS_EAST_EXIT,
    ENTR_GERUDO_VALLEY_WEST_EXIT,
    ENTR_HAUNTED_WASTELAND_EAST_EXIT,
    ENTR_GERUDOS_FORTRESS_GATE_EXIT,
    ENTR_DESERT_COLOSSUS_EAST_EXIT,
    ENTR_HAUNTED_WASTELAND_WEST_EXIT,
    ENTR_MARKET_SOUTH_EXIT,
    ENTR_MARKET_ENTRANCE_NORTH_EXIT,
    ENTR_CASTLE_GROUNDS_SOUTH_EXIT,
    ENTR_MARKET_DAY_CASTLE_EXIT,
    ENTR_TEMPLE_OF_TIME_EXTERIOR_DAY_GOSSIP_STONE_EXIT,
    ENTR_MARKET_DAY_TEMPLE_EXIT,
    ENTR_GRAVEYARD_ENTRANCE,
    ENTR_KAKARIKO_VILLAGE_SOUTHEAST_EXIT,
    ENTR_DEATH_MOUNTAIN_TRAIL_BOTTOM_EXIT,
    ENTR_KAKARIKO_VILLAGE_GUARD_GATE,
    ENTR_GORON_CITY_UPPER_EXIT,
    ENTR_DEATH_MOUNTAIN_TRAIL_GC_EXIT,
    ENTR_DEATH_MOUNTAIN_CRATER_GC_EXIT,
    ENTR_GORON_CITY_DARUNIA_ROOM_EXIT,
    ENTR_DEATH_MOUNTAIN_CRATER_UPPER_EXIT,
    ENTR_DEATH_MOUNTAIN_TRAIL_SUMMIT_EXIT,
    ENTR_ZORAS_DOMAIN_ENTRANCE,
    ENTR_ZORAS_RIVER_WATERFALL_EXIT,
    ENTR_ZORAS_FOUNTAIN_TUNNEL_EXIT,
    ENTR_ZORAS_DOMAIN_KING_ZORA_EXIT,
    ENTR_LAKE_HYLIA_RIVER_EXIT,
    ENTR_HYRULE_FIELD_OWL_DROP,
    ENTR_KAKARIKO_VILLAGE_OWL_DROP,
    ENTR_LINKS_HOUSE_CHILD_SPAWN,
    ENTR_HYRULE_FIELD_10,
    ENTR_SACRED_FOREST_MEADOW_WARP_PAD,
    ENTR_DEATH_MOUNTAIN_CRATER_WARP_PAD,
    ENTR_LAKE_HYLIA_WARP_PAD,
    ENTR_DESERT_COLOSSUS_WARP_PAD,
    ENTR_GRAVEYARD_WARP_PAD,
    ENTR_TEMPLE_OF_TIME_WARP_PAD,
    ENTR_DEKU_TREE_BOSS_ENTRANCE,
    ENTR_DEKU_TREE_BOSS_DOOR,
    ENTR_DODONGOS_CAVERN_BOSS_ENTRANCE,
    ENTR_DODONGOS_CAVERN_BOSS_DOOR,
    ENTR_JABU_JABU_BOSS_ENTRANCE,
    ENTR_JABU_JABU_BOSS_DOOR,
    ENTR_FOREST_TEMPLE_BOSS_ENTRANCE,
    ENTR_FOREST_TEMPLE_BOSS_DOOR,
    ENTR_FIRE_TEMPLE_BOSS_ENTRANCE,
    ENTR_FIRE_TEMPLE_BOSS_DOOR,
    ENTR_WATER_TEMPLE_BOSS_ENTRANCE,
    ENTR_WATER_TEMPLE_BOSS_DOOR,
    ENTR_SPIRIT_TEMPLE_BOSS_ENTRANCE,
    ENTR_SPIRIT_TEMPLE_BOSS_DOOR,
    ENTR_SHADOW_TEMPLE_BOSS_ENTRANCE,
    ENTR_SHADOW_TEMPLE_BOSS_DOOR,
};

static void RandomGrotto_WaitOpen(DoorAna* doorAna, PlayState* play) {
    Actor* actor = &doorAna->actor;
    Player* player = GET_PLAYER(play);
    if (Math_StepToF(&actor->scale.x, 0.01f, 0.001f)) {
        if ((actor->targetMode != 0) && (play->transitionTrigger == TRANS_TRIGGER_OFF) &&
            (player->stateFlags1 & PLAYER_STATE1_FLOOR_DISABLED) && (player->av1.actionVar1 == 0)) {
            Random_Init(rand() % 0xFFFFFFFF);
            play->nextEntranceIndex = RandomElement(validEntrances);
            DoorAna_SetupAction((DoorAna*)actor, DoorAna_GrabPlayer);
        } else {
            if (!Player_InCsMode(play) && !(player->stateFlags1 & (PLAYER_STATE1_ON_HORSE | PLAYER_STATE1_IN_WATER)) &&
                actor->xzDistToPlayer <= 15.0f && -50.0f <= actor->yDistToPlayer && actor->yDistToPlayer <= 15.0f) {
                player->stateFlags1 |= PLAYER_STATE1_FLOOR_DISABLED;
                actor->targetMode = 1;
            } else {
                actor->targetMode = 0;
            }
        }
    }
    Actor_SetScale(actor, actor->scale.x);
}

static void SpawnRandomGrotto() {
    if (gPlayState->sceneNum == SCENE_TEMPLE_OF_TIME_EXTERIOR_DAY ||
        gPlayState->sceneNum == SCENE_TEMPLE_OF_TIME_EXTERIOR_NIGHT ||
        gPlayState->sceneNum == SCENE_TEMPLE_OF_TIME_EXTERIOR_RUINS) {
        return;
    }

    Vec3f pos;
    pos.y = 9999.0f;
    int spawnAttempts = 0;
    while (spawnAttempts < 50) {
        if (GET_PLAYER(gPlayState) != nullptr) {
            pos.x = GET_PLAYER(gPlayState)->actor.world.pos.x;
            pos.z = GET_PLAYER(gPlayState)->actor.world.pos.z;
        } else {
            pos.x = 0;
            pos.z = 0;
        }
        // X/Z anywhere from -1000.0 to +1000.0 from player
        pos.x += (float)(Random(0, 5000)) - 2500.0f;
        pos.z += (float)(Random(0, 5000)) - 2500.0f;

        raycastResult = BgCheck_AnyRaycastFloor1(&gPlayState->colCtx, &snowballPoly, &pos);

        if (raycastResult > BGCHECK_Y_MIN) {
            Actor* grotto = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_DOOR_ANA, pos.x, raycastResult, pos.z,
                                        0, 0, 0, 0, false);
            DoorAna_SetupAction((DoorAna*)grotto, RandomGrotto_WaitOpen);
            break;
        }

        spawnAttempts++;
    }
}

static void OnConfigurationChanged() {
    COND_HOOK(OnSceneSpawnActors, CVarGetInteger(CVAR("Snowballs"), 0), SpawnSnowballs);
    COND_HOOK(OnPlayerUpdate, CVarGetInteger(CVAR("SuperBonk"), 0), []() {
        Player* player = GET_PLAYER(gPlayState);
        if (player->actor.bgCheckFlags & 0x08 && ABS(player->linearVelocity) > 15.0f) {
            player->yaw = ((player->actor.wallYaw - player->yaw) + player->actor.wallYaw) - 0x8000;
            Player_PlaySfx(&player->actor, NA_SE_PL_BODY_HIT);
        }
    });

    COND_HOOK(OnPlayerBonk, CVarGetInteger(CVAR("SuperBonk"), 0), []() {
        Player* player = GET_PLAYER(gPlayState);

        player->linearVelocity = -100.0f;
    });
    COND_HOOK(OnSceneSpawnActors, CVarGetInteger(CVAR("Icebergs"), 0), SpawnIcebergs);
    COND_HOOK(OnSceneSpawnActors, CVarGetInteger(CVAR("DownTheRabbitHole"), 0), SpawnRandomGrotto);
}

static void RegisterMenu() {
    WidgetPath path = { "Holiday", "Gameplay", SECTION_COLUMN_1 };

    SohGui::mSohMenu->AddWidget(path, "Snowballs", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("Snowballs"))
        .Options(
            UIWidgets::CheckboxOptions().Tooltip("Rogue snowballs will spawn in Hyrule Field and Kakariko Village."));

    SohGui::mSohMenu->AddWidget(path, "Lake Hylia Icebergs", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("Icebergs"))
        .Options(UIWidgets::CheckboxOptions().Tooltip("Icebergs will spawn in Lake Hylia."));

    SohGui::mSohMenu->AddWidget(path, "Down the Rabbit Hole", WIDGET_CVAR_CHECKBOX)
        .CVar(CVAR("DownTheRabbitHole"))
        .Options(UIWidgets::CheckboxOptions().Tooltip(
            "Random grottos will spawn throughout Hyrule. Who knows where they will take you?"));

    SohGui::mSohMenu->AddWidget(path, "Super Bonk", WIDGET_CVAR_CHECKBOX).CVar(CVAR("SuperBonk"));

    path.sidebarName = "Visual";
    path.column = SECTION_COLUMN_1;

    SohGui::mSohMenu->AddWidget(path, "Snow Everywhere", WIDGET_CVAR_CHECKBOX)
        .CVar("gHoliday.Visual.SnowingWeather")
        .Options(
            UIWidgets::CheckboxOptions().Tooltip("Enables the snow fall effect in all areas, colors trees and paths "
                                                 "white. Best paired with the official holiday texture pack."));

    SohGui::mSohMenu->AddWidget(path, "Festive Hats", WIDGET_CVAR_CHECKBOX)
        .CVar("gHoliday.Visual.Hats")
        .Options(UIWidgets::CheckboxOptions().Tooltip("Link and NPCs will wear festive holiday hats."));

    SohGui::mSohMenu->AddWidget(path, "Present Chests", WIDGET_CVAR_CHECKBOX)
        .CVar("gHoliday.Visual.PresentChests")
        .Options(UIWidgets::CheckboxOptions().Tooltip("Treasure chests will use present textures."));
}

#define PATCH_GFX(path, name, cvar, index, instruction)             \
    if (CVarGetInteger(cvar, 0)) {                                  \
        ResourceMgr_PatchGfxByName(path, name, index, instruction); \
    } else {                                                        \
        ResourceMgr_UnpatchGfxByName(path, name);                   \
    }

static void PatchTrees() {
    PATCH_GFX(object_wood02_DL_007968, "Tree1", "gHoliday.Visual.SnowingWeather", 17,
              gsDPSetPrimColor(0, 0, 255, 255, 255, 255));
    PATCH_GFX(object_wood02_DL_000090, "Tree2", "gHoliday.Visual.SnowingWeather", 17,
              gsDPSetPrimColor(0, 0, 200, 255, 255, 255));
    PATCH_GFX(object_wood02_DL_000340, "Tree3", "gHoliday.Visual.SnowingWeather", 17,
              gsDPSetPrimColor(0, 0, 255, 255, 255, 255));
    PATCH_GFX(object_wood02_DL_000340, "Tree4", "gHoliday.Visual.SnowingWeather", 24,
              gsDPSetPrimColor(0, 0, 255, 255, 255, 255));
    PATCH_GFX(spot00_room_0DL_0139A8, "Path1", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 100, 150, 255, 60));
    PATCH_GFX(spot00_room_0DL_013250, "Path2", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 100, 150, 255, 60));
    PATCH_GFX(spot00_room_0DL_0143C8, "Path3", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 100, 150, 255, 60));
    PATCH_GFX(spot04_room_0DL_018048, "Path4", "gHoliday.Visual.SnowingWeather", 24,
              gsDPSetPrimColor(0, 0, 100, 150, 255, 60));
    PATCH_GFX(spot04_room_1DL_007810, "Path5", "gHoliday.Visual.SnowingWeather", 24,
              gsDPSetPrimColor(0, 0, 100, 150, 255, 60));
    PATCH_GFX(spot20_room_0DL_0062D0, "Path6", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));
    PATCH_GFX(spot20_room_0DL_004460, "Path8", "gHoliday.Visual.SnowingWeather", 31,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));
    PATCH_GFX(spot20_room_0DL_004460, "Path9", "gHoliday.Visual.SnowingWeather", 118,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));
    PATCH_GFX(spot20_room_0DL_0065E8, "Path10", "gHoliday.Visual.SnowingWeather", 24,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));
    PATCH_GFX(spot03_room_0DL_00C4B0, "Path11", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));
    PATCH_GFX(spot15_room_0DL_00C748, "Path12", "gHoliday.Visual.SnowingWeather", 23,
              gsDPSetPrimColor(0, 0, 200, 230, 255, 30));

    static u32 blizzardActiveTimer = 0;
    blizzardActiveTimer = 0;
    CVarClear("gHoliday.Visual.SnowingWeatherActive");
    COND_HOOK(OnPlayerUpdate, CVarGetInteger("gHoliday.Visual.SnowingWeather", 0), []() {
        // Every frame has a 1/1000 chance to start a blizzard if there isn't one already
        if (blizzardActiveTimer == 0 && rand() % 1000 == 0) {
            blizzardActiveTimer = 20 * 20; // Lasts for 20 seconds
            CVarSetInteger("gHoliday.Visual.SnowingWeatherActive", 2);
        }
        if (blizzardActiveTimer > 0) {
            blizzardActiveTimer--;
        }
        if (blizzardActiveTimer == 0) {
            CVarClear("gHoliday.Visual.SnowingWeatherActive");
        } else if (blizzardActiveTimer < 20) {
            CVarSetInteger("gHoliday.Visual.SnowingWeatherActive", 1);
        }
    });
}

static RegisterShipInitFunc initFuncTrees(PatchTrees, { "gHoliday.Visual.SnowingWeather" });

static RegisterShipInitFunc initFunc(OnConfigurationChanged, { CVAR("Snowballs"), CVAR("Icebergs"),
                                                               CVAR("DownTheRabbitHole"), CVAR("SuperBonk") });
static RegisterMenuInitFunc menuInitFunc(RegisterMenu);
