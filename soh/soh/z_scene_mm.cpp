
#include "OTRGlobals.h"

extern "C" {
#include "macros.h"

}

static MMEntranceTableEntry sMayorsResidenceEntrance0[] = {
    { SCENE_SONCHONOIE, 0, 0x4102 },
};

static MMEntranceTableEntry sMayorsResidenceEntrance1[] = {
    { SCENE_SONCHONOIE, 1, 0x4102 },
};

static MMEntranceTableEntry sMayorsResidenceEntrance2[] = {
    { SCENE_SONCHONOIE, 2, 0x4102 },
};

static MMEntranceTableEntry* sMayorsResidenceEntranceTable[] = {
    sMayorsResidenceEntrance0,
    sMayorsResidenceEntrance1,
    sMayorsResidenceEntrance2,
};

static MMEntranceTableEntry sMajorasLairEntrance0[] = {
    { -SCENE_LAST_BS, 0, 0x0387 },
};

static MMEntranceTableEntry* sMajorasLairEntranceTable[] = {
    sMajorasLairEntrance0,
};

static MMEntranceTableEntry sMagicHagsPotionShopEntrance0[] = {
    { SCENE_WITCH_SHOP, 0, 0x4102 },
};

static MMEntranceTableEntry* sMagicHagsPotionShopEntranceTable[] = {
    sMagicHagsPotionShopEntrance0,
};

static MMEntranceTableEntry sRanchHouseEntrance0[] = {
    { SCENE_OMOYA, 0, 0x0102 },
};

static MMEntranceTableEntry sRanchHouseEntrance1[] = {
    { SCENE_OMOYA, 1, 0x4102 },
};

static MMEntranceTableEntry* sRanchHouseEntranceTable[] = {
    sRanchHouseEntrance0,
    sRanchHouseEntrance1,
};

static MMEntranceTableEntry sHoneyAndDarlingsShopEntrance0[] = {
    { SCENE_BOWLING, 0, 0x4102 },
};

static MMEntranceTableEntry* sHoneyAndDarlingsShopEntranceTable[] = {
    sHoneyAndDarlingsShopEntrance0,
};

static MMEntranceTableEntry sBeneathTheGraveryardEntrance0[] = {
    { -SCENE_HAKASHITA, 0, 0x4102 },
};

static MMEntranceTableEntry sBeneathTheGraveryardEntrance1[] = {
    { -SCENE_HAKASHITA, 1, 0x4102 },
};

static MMEntranceTableEntry* sBeneathTheGraveryardEntranceTable[] = {
    sBeneathTheGraveryardEntrance0,
    sBeneathTheGraveryardEntrance1,
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance0[] = {
    { SCENE_20SICHITAI2, 0, 0xCA14 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance1[] = {
    { SCENE_20SICHITAI2, 1, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance2[] = {
    { SCENE_20SICHITAI2, 2, 0xC102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance3[] = {
    { SCENE_20SICHITAI2, 3, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance4[] = {
    { SCENE_20SICHITAI2, 4, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance5[] = {
    { SCENE_20SICHITAI2, 5, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance6[] = {
    { SCENE_20SICHITAI2, 6, 0x0102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance7[] = {
    { SCENE_20SICHITAI2, 7, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance8[] = {
    { SCENE_20SICHITAI2, 8, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance9[] = {
    { SCENE_20SICHITAI2, 9, 0x4A14 },
};

static MMEntranceTableEntry sSouthernSwampClearedEntrance10[] = {
    { SCENE_20SICHITAI2, 10, 0x4A14 },
};

static MMEntranceTableEntry* sSouthernSwampClearedEntranceTable[] = {
    sSouthernSwampClearedEntrance0, sSouthernSwampClearedEntrance1,  sSouthernSwampClearedEntrance2,
    sSouthernSwampClearedEntrance3, sSouthernSwampClearedEntrance4,  sSouthernSwampClearedEntrance5,
    sSouthernSwampClearedEntrance6, sSouthernSwampClearedEntrance7,  sSouthernSwampClearedEntrance8,
    sSouthernSwampClearedEntrance9, sSouthernSwampClearedEntrance10,
};

static MMEntranceTableEntry sCuriosityShopEntrance0[] = {
    { SCENE_AYASHIISHOP, 0, 0x4102 },
};

static MMEntranceTableEntry sCuriosityShopEntrance1[] = {
    { SCENE_AYASHIISHOP, 1, 0x0102 },
};

static MMEntranceTableEntry sCuriosityShopEntrance2[] = {
    { SCENE_AYASHIISHOP, 2, 0x8A95 },
};

static MMEntranceTableEntry sCuriosityShopEntrance3[] = {
    { SCENE_AYASHIISHOP, 3, 0x8102 },
};

static MMEntranceTableEntry* sCuriosityShopEntranceTable[] = {
    sCuriosityShopEntrance0,
    sCuriosityShopEntrance1,
    sCuriosityShopEntrance2,
    sCuriosityShopEntrance3,
};

static MMEntranceTableEntry sIkanaCanyonEntrance0[] = {
    { SCENE_IKANA, 0, 0xCA14 }, { SCENE_IKANA, 0, 0x8A14 }, { SCENE_IKANA, 0, 0x0A14 },
    { SCENE_IKANA, 0, 0x4A14 }, { SCENE_IKANA, 0, 0x8102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance1[] = {
    { SCENE_IKANA, 1, 0x4102 },
    { SCENE_IKANA, 1, 0x4102 },
    { SCENE_IKANA, 1, 0xCA14 },
    { SCENE_IKANA, 1, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance2[] = {
    { SCENE_IKANA, 2, 0x4102 },
    { SCENE_IKANA, 2, 0x4102 },
    { SCENE_IKANA, 2, 0x4102 },
    { SCENE_IKANA, 2, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance3[] = {
    { SCENE_IKANA, 3, 0x4102 },
    { SCENE_IKANA, 3, 0x4102 },
    { SCENE_IKANA, 3, 0x4102 },
    { SCENE_IKANA, 3, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance4[] = {
    { SCENE_IKANA, 4, 0x4A14 },
    { SCENE_IKANA, 4, 0x4A14 },
    { SCENE_IKANA, 4, 0x4A14 },
    { SCENE_IKANA, 4, 0x4A14 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance5[] = {
    { SCENE_IKANA, 5, 0x4102 },
    { SCENE_IKANA, 5, 0x4102 },
    { SCENE_IKANA, 5, 0x4102 },
    { SCENE_IKANA, 5, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance6[] = {
    { SCENE_IKANA, 6, 0x4102 },
    { SCENE_IKANA, 6, 0x4102 },
    { SCENE_IKANA, 6, 0x4102 },
    { SCENE_IKANA, 6, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance7[] = {
    { SCENE_IKANA, 7, 0x4A14 },
    { SCENE_IKANA, 7, 0x4A14 },
    { SCENE_IKANA, 7, 0x4A14 },
    { SCENE_IKANA, 7, 0x4A14 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance8[] = {
    { SCENE_IKANA, 8, 0x4102 },
    { SCENE_IKANA, 8, 0x4102 },
    { SCENE_IKANA, 8, 0x4102 },
    { SCENE_IKANA, 8, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance9[] = {
    { SCENE_IKANA, 9, 0x4A14 },
    { SCENE_IKANA, 9, 0x4A14 },
    { SCENE_IKANA, 9, 0x4A14 },
    { SCENE_IKANA, 9, 0x4A14 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance10[] = {
    { SCENE_IKANA, 10, 0x4A14 },
    { SCENE_IKANA, 10, 0x4A14 },
    { SCENE_IKANA, 10, 0x4A14 },
    { SCENE_IKANA, 10, 0x4A14 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance11[] = {
    { SCENE_IKANA, 11, 0x4102 },
    { SCENE_IKANA, 11, 0x4102 },
    { SCENE_IKANA, 11, 0x4102 },
    { SCENE_IKANA, 11, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance12[] = {
    { SCENE_IKANA, 12, 0x4102 },
    { SCENE_IKANA, 12, 0x4102 },
    { SCENE_IKANA, 12, 0x4102 },
    { SCENE_IKANA, 12, 0x4102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance13[] = {
    { SCENE_IKANA, 13, 0x8102 },
    { SCENE_IKANA, 13, 0x8102 },
    { SCENE_IKANA, 13, 0x8102 },
    { SCENE_IKANA, 13, 0x8102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance14[] = {
    { SCENE_IKANA, 14, 0x8102 },
    { SCENE_IKANA, 14, 0x8102 },
    { SCENE_IKANA, 14, 0x8102 },
    { SCENE_IKANA, 14, 0x8102 },
};

static MMEntranceTableEntry sIkanaCanyonEntrance15[] = {
    { SCENE_IKANA, 15, 0x8102 },
    { SCENE_IKANA, 15, 0x8102 },
    { SCENE_IKANA, 15, 0x8102 },
    { SCENE_IKANA, 15, 0x0183 },
};

static MMEntranceTableEntry* sIkanaCanyonEntranceTable[] = {
    sIkanaCanyonEntrance0,  sIkanaCanyonEntrance1,  sIkanaCanyonEntrance2,  sIkanaCanyonEntrance3,
    sIkanaCanyonEntrance4,  sIkanaCanyonEntrance5,  sIkanaCanyonEntrance6,  sIkanaCanyonEntrance7,
    sIkanaCanyonEntrance8,  sIkanaCanyonEntrance9,  sIkanaCanyonEntrance10, sIkanaCanyonEntrance11,
    sIkanaCanyonEntrance12, sIkanaCanyonEntrance13, sIkanaCanyonEntrance14, sIkanaCanyonEntrance15,
};

static MMEntranceTableEntry sPiratesFortressEntrance0[] = {
    { SCENE_KAIZOKU, 0, 0x8102 },
    { SCENE_KAIZOKU, 0, 0x8102 },
    { SCENE_KAIZOKU, 0, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance1[] = {
    { SCENE_KAIZOKU, 1, 0x8102 },
    { SCENE_KAIZOKU, 1, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance2[] = {
    { SCENE_KAIZOKU, 2, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance3[] = {
    { SCENE_KAIZOKU, 3, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance4[] = {
    { SCENE_KAIZOKU, 4, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance5[] = {
    { SCENE_KAIZOKU, 5, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance6[] = {
    { SCENE_KAIZOKU, 6, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance7[] = {
    { SCENE_KAIZOKU, 7, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance8[] = {
    { SCENE_KAIZOKU, 8, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance9[] = {
    { SCENE_KAIZOKU, 9, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance10[] = {
    { SCENE_KAIZOKU, 10, 0x8A95 },
};

static MMEntranceTableEntry sPiratesFortressEntrance11[] = {
    { SCENE_KAIZOKU, 11, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance12[] = {
    { SCENE_KAIZOKU, 12, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance13[] = {
    { SCENE_KAIZOKU, 13, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressEntrance14[] = {
    { SCENE_KAIZOKU, 14, 0x8102 },
};

static MMEntranceTableEntry* sPiratesFortressEntranceTable[] = {
    sPiratesFortressEntrance0,  sPiratesFortressEntrance1,  sPiratesFortressEntrance2,  sPiratesFortressEntrance3,
    sPiratesFortressEntrance4,  sPiratesFortressEntrance5,  sPiratesFortressEntrance6,  sPiratesFortressEntrance7,
    sPiratesFortressEntrance8,  sPiratesFortressEntrance9,  sPiratesFortressEntrance10, sPiratesFortressEntrance11,
    sPiratesFortressEntrance12, sPiratesFortressEntrance13, sPiratesFortressEntrance14,
};

static MMEntranceTableEntry sMilkBarEntrance0[] = {
    { SCENE_MILK_BAR, 0, 0x4102 }, { SCENE_MILK_BAR, 0, 0x8102 }, { SCENE_MILK_BAR, 0, 0x8102 },
    { SCENE_MILK_BAR, 0, 0x8102 }, { SCENE_MILK_BAR, 0, 0x8102 },
};

static MMEntranceTableEntry* sMilkBarEntranceTable[] = {
    sMilkBarEntrance0,
};

static MMEntranceTableEntry sStoneTowerTempleEntrance0[] = {
    { -SCENE_INISIE_N, 0, 0xC102 },
};

static MMEntranceTableEntry sStoneTowerTempleEntrance1[] = {
    { -SCENE_INISIE_N, 1, 0x4102 },
};

static MMEntranceTableEntry* sStoneTowerTempleEntranceTable[] = {
    sStoneTowerTempleEntrance0,
    sStoneTowerTempleEntrance1,
};

static MMEntranceTableEntry sTreasureChestShopEntrance0[] = {
    { SCENE_TAKARAYA, 0, 0x4102 },
};

static MMEntranceTableEntry sTreasureChestShopEntrance1[] = {
    { SCENE_TAKARAYA, 1, 0x0102 },
};

static MMEntranceTableEntry* sTreasureChestShopEntranceTable[] = {
    sTreasureChestShopEntrance0,
    sTreasureChestShopEntrance1,
};

static MMEntranceTableEntry sStoneTowerTempleInvertedEntrance0[] = {
    { -SCENE_INISIE_R, 0, 0xC102 },
};

static MMEntranceTableEntry sStoneTowerTempleInvertedEntrance1[] = {
    { -SCENE_INISIE_R, 1, 0x8102 },
};

static MMEntranceTableEntry sStoneTowerTempleInvertedEntrance2[] = {
    { -SCENE_INISIE_R, 2, 0x8102 },
};

static MMEntranceTableEntry* sStoneTowerTempleInvertedEntranceTable[] = {
    sStoneTowerTempleInvertedEntrance0,
    sStoneTowerTempleInvertedEntrance1,
    sStoneTowerTempleInvertedEntrance2,
};

static MMEntranceTableEntry sClockTowerRooftopEntrance0[] = {
    { -SCENE_OKUJOU, 0, 0x0102 },
    { -SCENE_OKUJOU, 0, 0x8102 },
    { -SCENE_OKUJOU, 0, 0x0102 },
    { -SCENE_OKUJOU, 0, 0x0102 },
};

static MMEntranceTableEntry sClockTowerRooftopEntrance1[] = {
    { -SCENE_OKUJOU, 1, 0x0102 },
    { -SCENE_OKUJOU, 1, 0x0102 },
    { -SCENE_OKUJOU, 1, 0x0102 },
};

static MMEntranceTableEntry sClockTowerRooftopEntrance2[] = {
    { -SCENE_OKUJOU, 2, 0x858B },
    { -SCENE_OKUJOU, 2, 0x858B },
    { -SCENE_OKUJOU, 2, 0x8102 },
};

static MMEntranceTableEntry* sClockTowerRooftopEntranceTable[] = {
    sClockTowerRooftopEntrance0,
    sClockTowerRooftopEntrance1,
    sClockTowerRooftopEntrance2,
};

static MMEntranceTableEntry sOpeningDungeonEntrance0[] = {
    { -SCENE_OPENINGDAN, 0, 0x0102 },
    { -SCENE_OPENINGDAN, 0, 0x8102 },
};

static MMEntranceTableEntry sOpeningDungeonEntrance1[] = {
    { -SCENE_OPENINGDAN, 1, 0x0102 },
};

static MMEntranceTableEntry sOpeningDungeonEntrance2[] = {
    { -SCENE_OPENINGDAN, 2, 0x0102 },
};

static MMEntranceTableEntry sOpeningDungeonEntrance3[] = {
    { -SCENE_OPENINGDAN, 3, 0x0102 },
};

static MMEntranceTableEntry sOpeningDungeonEntrance4[] = {
    { -SCENE_OPENINGDAN, 4, 0x058B },
};

static MMEntranceTableEntry* sOpeningDungeonEntranceTable[] = {
    sOpeningDungeonEntrance0, sOpeningDungeonEntrance1, sOpeningDungeonEntrance2,
    sOpeningDungeonEntrance3, sOpeningDungeonEntrance4,
};

static MMEntranceTableEntry sWoodfallTempleEntrance0[] = {
    { -SCENE_MITURIN, 0, 0x4102 },
};

static MMEntranceTableEntry sWoodfallTempleEntrance1[] = {
    { -SCENE_MITURIN, 1, 0x0102 },
};

static MMEntranceTableEntry sWoodfallTempleEntrance2[] = {
    { -SCENE_MITURIN, 2, 0x0102 },
};

static MMEntranceTableEntry* sWoodfallTempleEntranceTable[] = {
    sWoodfallTempleEntrance0,
    sWoodfallTempleEntrance1,
    sWoodfallTempleEntrance2,
};

static MMEntranceTableEntry sPathToMountainVillageEntrance0[] = {
    { SCENE_13HUBUKINOMITI, 0, 0x8A14 },
    { SCENE_13HUBUKINOMITI, 0, 0x8A14 },
};

static MMEntranceTableEntry sPathToMountainVillageEntrance1[] = {
    { SCENE_13HUBUKINOMITI, 1, 0x8A14 },
    { SCENE_13HUBUKINOMITI, 1, 0x8A14 },
};

static MMEntranceTableEntry* sPathToMountainVillageEntranceTable[] = {
    sPathToMountainVillageEntrance0,
    sPathToMountainVillageEntrance1,
};

static MMEntranceTableEntry sIkanaCastleEntrance0[] = {
    { -SCENE_CASTLE, 0, 0x4102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance1[] = {
    { -SCENE_CASTLE, 1, 0x4102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance2[] = {
    { -SCENE_CASTLE, 2, 0x8102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance3[] = {
    { -SCENE_CASTLE, 3, 0x8102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance4[] = {
    { -SCENE_CASTLE, 4, 0x8102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance5[] = {
    { -SCENE_CASTLE, 5, 0x8102 },
};

static MMEntranceTableEntry sIkanaCastleEntrance6[] = {
    { -SCENE_CASTLE, 6, 0x8102 },
};

static MMEntranceTableEntry* sIkanaCastleEntranceTable[] = {
    sIkanaCastleEntrance0, sIkanaCastleEntrance1, sIkanaCastleEntrance2, sIkanaCastleEntrance3,
    sIkanaCastleEntrance4, sIkanaCastleEntrance5, sIkanaCastleEntrance6,
};

static MMEntranceTableEntry sDekuScrubPlaygroundEntrance0[] = {
    { SCENE_DEKUTES, 0, 0x0102 },
};

static MMEntranceTableEntry sDekuScrubPlaygroundEntrance1[] = {
    { SCENE_DEKUTES, 1, 0x0102 },
};

static MMEntranceTableEntry* sDekuScrubPlaygroundEntranceTable[] = {
    sDekuScrubPlaygroundEntrance0,
    sDekuScrubPlaygroundEntrance1,
};

static MMEntranceTableEntry sOdolwasLairEntrance0[] = {
    { -SCENE_MITURIN_BS, 0, 0x8102 },
};

static MMEntranceTableEntry* sOdolwasLairEntranceTable[] = {
    sOdolwasLairEntrance0,
};

static MMEntranceTableEntry sTownShootingGalleryEntrance0[] = {
    { SCENE_SYATEKI_MIZU, 0, 0x4102 },
};

static MMEntranceTableEntry sTownShootingGalleryEntrance1[] = {
    { SCENE_SYATEKI_MIZU, 1, 0x0102 },
};

static MMEntranceTableEntry* sTownShootingGalleryEntranceTable[] = {
    sTownShootingGalleryEntrance0,
    sTownShootingGalleryEntrance1,
};

static MMEntranceTableEntry sSnowheadTempleEntrance0[] = {
    { -SCENE_HAKUGIN, 0, 0x4102 },
};

static MMEntranceTableEntry sSnowheadTempleEntrance1[] = {
    { -SCENE_HAKUGIN, 1, 0x4102 },
};

static MMEntranceTableEntry* sSnowheadTempleEntranceTable[] = {
    sSnowheadTempleEntrance0,
    sSnowheadTempleEntrance1,
};

static MMEntranceTableEntry sMilkRoadEntrance0[] = {
    { SCENE_ROMANYMAE, 0, 0xCA14 },
};

static MMEntranceTableEntry sMilkRoadEntrance1[] = {
    { SCENE_ROMANYMAE, 1, 0x4A14 },
};

static MMEntranceTableEntry sMilkRoadEntrance2[] = {
    { SCENE_ROMANYMAE, 2, 0x4A14 },
};

static MMEntranceTableEntry sMilkRoadEntrance3[] = {
    { SCENE_ROMANYMAE, 3, 0x4A14 },
};

static MMEntranceTableEntry sMilkRoadEntrance4[] = {
    { SCENE_ROMANYMAE, 4, 0x4A14 },
};

static MMEntranceTableEntry sMilkRoadEntrance5[] = {
    { SCENE_ROMANYMAE, 5, 0x0102 },
};

static MMEntranceTableEntry sMilkRoadEntrance6[] = {
    { SCENE_ROMANYMAE, 6, 0x0102 },
};

static MMEntranceTableEntry* sMilkRoadEntranceTable[] = {
    sMilkRoadEntrance0, sMilkRoadEntrance1, sMilkRoadEntrance2, sMilkRoadEntrance3,
    sMilkRoadEntrance4, sMilkRoadEntrance5, sMilkRoadEntrance6,
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance0[] = {
    { SCENE_PIRATE, 0, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance1[] = {
    { SCENE_PIRATE, 1, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance2[] = {
    { SCENE_PIRATE, 2, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance3[] = {
    { SCENE_PIRATE, 3, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance4[] = {
    { SCENE_PIRATE, 4, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance5[] = {
    { SCENE_PIRATE, 5, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance6[] = {
    { SCENE_PIRATE, 6, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance7[] = {
    { SCENE_PIRATE, 7, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance8[] = {
    { SCENE_PIRATE, 8, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance9[] = {
    { SCENE_PIRATE, 9, 0x8993 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance10[] = {
    { SCENE_PIRATE, 10, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance11[] = {
    { SCENE_PIRATE, 11, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance12[] = {
    { SCENE_PIRATE, 12, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance13[] = {
    { SCENE_PIRATE, 13, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance14[] = {
    { SCENE_PIRATE, 14, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressInteriorEntrance15[] = {
    { SCENE_PIRATE, 15, 0x8102 },
};

static MMEntranceTableEntry* sPiratesFortressInteriorEntranceTable[] = {
    sPiratesFortressInteriorEntrance0,  sPiratesFortressInteriorEntrance1,  sPiratesFortressInteriorEntrance2,
    sPiratesFortressInteriorEntrance3,  sPiratesFortressInteriorEntrance4,  sPiratesFortressInteriorEntrance5,
    sPiratesFortressInteriorEntrance6,  sPiratesFortressInteriorEntrance7,  sPiratesFortressInteriorEntrance8,
    sPiratesFortressInteriorEntrance9,  sPiratesFortressInteriorEntrance10, sPiratesFortressInteriorEntrance11,
    sPiratesFortressInteriorEntrance12, sPiratesFortressInteriorEntrance13, sPiratesFortressInteriorEntrance14,
    sPiratesFortressInteriorEntrance15,
};

static MMEntranceTableEntry sSwampShootingGalleryEntrance0[] = {
    { SCENE_SYATEKI_MORI, 0, 0x4102 },
};

static MMEntranceTableEntry* sSwampShootingGalleryEntranceTable[] = {
    sSwampShootingGalleryEntrance0,
};

static MMEntranceTableEntry sPinnacleRockEntrance0[] = {
    { SCENE_SINKAI, 0, 0x4A14 },
};

static MMEntranceTableEntry sPinnacleRockEntrance1[] = {
    { SCENE_SINKAI, 1, 0x0A14 },
};

static MMEntranceTableEntry* sPinnacleRockEntranceTable[] = {
    sPinnacleRockEntrance0,
    sPinnacleRockEntrance1,
};

static MMEntranceTableEntry sFairyFountainEntrance0[] = {
    { SCENE_YOUSEI_IZUMI, 0, 0x4102 },
    { SCENE_YOUSEI_IZUMI, 0, 0x8102 },
};

static MMEntranceTableEntry sFairyFountainEntrance1[] = {
    { SCENE_YOUSEI_IZUMI, 1, 0x4102 },
};

static MMEntranceTableEntry sFairyFountainEntrance2[] = {
    { SCENE_YOUSEI_IZUMI, 2, 0x4102 },
};

static MMEntranceTableEntry sFairyFountainEntrance3[] = {
    { SCENE_YOUSEI_IZUMI, 3, 0x4102 },
};

static MMEntranceTableEntry sFairyFountainEntrance4[] = {
    { SCENE_YOUSEI_IZUMI, 4, 0x4102 },
};

static MMEntranceTableEntry sFairyFountainEntrance5[] = {
    { SCENE_YOUSEI_IZUMI, 5, 0x8183 },
};

static MMEntranceTableEntry sFairyFountainEntrance6[] = {
    { SCENE_YOUSEI_IZUMI, 6, 0x858B },
};

static MMEntranceTableEntry sFairyFountainEntrance7[] = {
    { SCENE_YOUSEI_IZUMI, 7, 0x858B },
};

static MMEntranceTableEntry sFairyFountainEntrance8[] = {
    { SCENE_YOUSEI_IZUMI, 8, 0x858B },
};

static MMEntranceTableEntry sFairyFountainEntrance9[] = {
    { SCENE_YOUSEI_IZUMI, 9, 0x858B },
};

static MMEntranceTableEntry* sFairyFountainEntranceTable[] = {
    sFairyFountainEntrance0, sFairyFountainEntrance1, sFairyFountainEntrance2, sFairyFountainEntrance3,
    sFairyFountainEntrance4, sFairyFountainEntrance5, sFairyFountainEntrance6, sFairyFountainEntrance7,
    sFairyFountainEntrance8, sFairyFountainEntrance9,
};

static MMEntranceTableEntry sSwampSpiderHouseEntrance0[] = {
    { -SCENE_KINSTA1, 0, 0x4102 },
};

static MMEntranceTableEntry* sSwampSpiderHouseEntranceTable[] = {
    sSwampSpiderHouseEntrance0,
};

static MMEntranceTableEntry sOceansideSpiderHouseEntrance0[] = {
    { -SCENE_KINDAN2, 0, 0x4102 },
};

static MMEntranceTableEntry* sOceansideSpiderHouseEntranceTable[] = {
    sOceansideSpiderHouseEntrance0,
};

static MMEntranceTableEntry sAstralObservatoryEntrance0[] = {
    { SCENE_TENMON_DAI, 0, 0x0102 },
};

static MMEntranceTableEntry sAstralObservatoryEntrance1[] = {
    { SCENE_TENMON_DAI, 1, 0x4102 },
};

static MMEntranceTableEntry sAstralObservatoryEntrance2[] = {
    { SCENE_TENMON_DAI, 2, 0x8115 },
};

static MMEntranceTableEntry* sAstralObservatoryEntranceTable[] = {
    sAstralObservatoryEntrance0,
    sAstralObservatoryEntrance1,
    sAstralObservatoryEntrance2,
};

static MMEntranceTableEntry sMoonDekuTrialEntrance0[] = {
    { -SCENE_LAST_DEKU, 0, 0x0387 },
};

static MMEntranceTableEntry* sMoonDekuTrialEntranceTable[] = {
    sMoonDekuTrialEntrance0,
};

static MMEntranceTableEntry sDekuPalaceEntrance0[] = {
    { SCENE_22DEKUCITY, 0, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance1[] = {
    { SCENE_22DEKUCITY, 1, 0x8A14 },
};

static MMEntranceTableEntry sDekuPalaceEntrance2[] = {
    { SCENE_22DEKUCITY, 2, 0xC102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance3[] = {
    { SCENE_22DEKUCITY, 3, 0xC102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance4[] = {
    { SCENE_22DEKUCITY, 4, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance5[] = {
    { SCENE_22DEKUCITY, 5, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance6[] = {
    { SCENE_22DEKUCITY, 6, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance7[] = {
    { SCENE_22DEKUCITY, 7, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance8[] = {
    { SCENE_22DEKUCITY, 8, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance9[] = {
    { SCENE_22DEKUCITY, 9, 0x4102 },
};

static MMEntranceTableEntry sDekuPalaceEntrance10[] = {
    { SCENE_22DEKUCITY, 10, 0x4102 },
};

static MMEntranceTableEntry* sDekuPalaceEntranceTable[] = {
    sDekuPalaceEntrance0, sDekuPalaceEntrance1, sDekuPalaceEntrance2,  sDekuPalaceEntrance3,
    sDekuPalaceEntrance4, sDekuPalaceEntrance5, sDekuPalaceEntrance6,  sDekuPalaceEntrance7,
    sDekuPalaceEntrance8, sDekuPalaceEntrance9, sDekuPalaceEntrance10,
};

static MMEntranceTableEntry sMountainSmithyEntrance0[] = {
    { SCENE_KAJIYA, 0, 0x4102 },
};

static MMEntranceTableEntry* sMountainSmithyEntranceTable[] = {
    sMountainSmithyEntrance0,
};

static MMEntranceTableEntry sTerminaFieldEntrance0[] = {
    { SCENE_00KEIKOKU, 0, 0x4102 },  { -SCENE_00KEIKOKU, 0, 0x0A14 }, { -SCENE_00KEIKOKU, 0, 0x0A14 },
    { -SCENE_00KEIKOKU, 0, 0x058B }, { SCENE_00KEIKOKU, 0, 0x0A14 },  { SCENE_00KEIKOKU, 0, 0x0A14 },
    { SCENE_00KEIKOKU, 0, 0x058B },  { SCENE_00KEIKOKU, 0, 0x8102 },  { SCENE_00KEIKOKU, 0, 0x0102 },
    { SCENE_00KEIKOKU, 0, 0x8102 },
};

static MMEntranceTableEntry sTerminaFieldEntrance1[] = {
    { SCENE_00KEIKOKU, 1, 0xCA14 },  { SCENE_00KEIKOKU, 1, 0x0A14 }, { SCENE_00KEIKOKU, 1, 0x058B },
    { -SCENE_00KEIKOKU, 1, 0x858B }, { SCENE_00KEIKOKU, 1, 0x0A14 }, { SCENE_00KEIKOKU, 1, 0x0A14 },
    { SCENE_00KEIKOKU, 1, 0x058B },  { SCENE_00KEIKOKU, 1, 0x858B }, { SCENE_00KEIKOKU, 1, 0x0102 },
    { SCENE_00KEIKOKU, 1, 0x8102 },
};

static MMEntranceTableEntry sTerminaFieldEntrance2[] = {
    { SCENE_00KEIKOKU, 2, 0xCA14 },  { -SCENE_00KEIKOKU, 2, 0x0A14 }, { -SCENE_00KEIKOKU, 2, 0x0A14 },
    { -SCENE_00KEIKOKU, 2, 0x058B }, { SCENE_00KEIKOKU, 2, 0x0A14 },  { SCENE_00KEIKOKU, 2, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance3[] = {
    { SCENE_00KEIKOKU, 3, 0xCA14 },  { -SCENE_00KEIKOKU, 3, 0x0A14 }, { -SCENE_00KEIKOKU, 3, 0x0A14 },
    { -SCENE_00KEIKOKU, 3, 0x058B }, { SCENE_00KEIKOKU, 3, 0x0A14 },  { SCENE_00KEIKOKU, 3, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance4[] = {
    { SCENE_00KEIKOKU, 4, 0xCA14 },  { -SCENE_00KEIKOKU, 4, 0x0A14 }, { -SCENE_00KEIKOKU, 4, 0x0A14 },
    { -SCENE_00KEIKOKU, 4, 0x058B }, { SCENE_00KEIKOKU, 4, 0x0A14 },  { SCENE_00KEIKOKU, 4, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance5[] = {
    { SCENE_00KEIKOKU, 5, 0xCA14 },  { -SCENE_00KEIKOKU, 5, 0x0A14 }, { -SCENE_00KEIKOKU, 5, 0x0A14 },
    { -SCENE_00KEIKOKU, 5, 0x858B }, { SCENE_00KEIKOKU, 5, 0x0A14 },  { SCENE_00KEIKOKU, 5, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance6[] = {
    { SCENE_00KEIKOKU, 6, 0x4102 },  { -SCENE_00KEIKOKU, 6, 0x0A14 }, { -SCENE_00KEIKOKU, 6, 0x0A14 },
    { -SCENE_00KEIKOKU, 6, 0x858B }, { SCENE_00KEIKOKU, 6, 0x0A14 },  { SCENE_00KEIKOKU, 6, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance7[] = {
    { SCENE_00KEIKOKU, 7, 0x4102 },  { -SCENE_00KEIKOKU, 7, 0x0A14 }, { -SCENE_00KEIKOKU, 7, 0x0A14 },
    { -SCENE_00KEIKOKU, 7, 0x858B }, { SCENE_00KEIKOKU, 7, 0x0A14 },  { SCENE_00KEIKOKU, 7, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance8[] = {
    { SCENE_00KEIKOKU, 8, 0x4102 },  { -SCENE_00KEIKOKU, 8, 0x0A14 }, { -SCENE_00KEIKOKU, 8, 0x0A14 },
    { -SCENE_00KEIKOKU, 8, 0x058B }, { SCENE_00KEIKOKU, 8, 0x0A14 },  { SCENE_00KEIKOKU, 8, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance9[] = {
    { SCENE_00KEIKOKU, 9, 0x4102 },  { -SCENE_00KEIKOKU, 9, 0x0A14 }, { -SCENE_00KEIKOKU, 9, 0x0A14 },
    { -SCENE_00KEIKOKU, 9, 0x058B }, { SCENE_00KEIKOKU, 9, 0x0A14 },  { SCENE_00KEIKOKU, 9, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance10[] = {
    { SCENE_00KEIKOKU, 10, 0x8A95 },  { -SCENE_00KEIKOKU, 10, 0x0A14 }, { -SCENE_00KEIKOKU, 10, 0x0A14 },
    { -SCENE_00KEIKOKU, 10, 0x058B }, { SCENE_00KEIKOKU, 10, 0x0A14 },  { SCENE_00KEIKOKU, 10, 0x0A95 },
};

static MMEntranceTableEntry sTerminaFieldEntrance11[] = {
    { SCENE_00KEIKOKU, 11, 0x4A14 },  { -SCENE_00KEIKOKU, 11, 0x0A14 }, { -SCENE_00KEIKOKU, 11, 0x0A14 },
    { -SCENE_00KEIKOKU, 11, 0x058B }, { SCENE_00KEIKOKU, 11, 0x0A14 },  { SCENE_00KEIKOKU, 11, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance12[] = {
    { SCENE_00KEIKOKU, 12, 0x0A14 },  { -SCENE_00KEIKOKU, 12, 0x0A14 }, { -SCENE_00KEIKOKU, 12, 0x0A14 },
    { -SCENE_00KEIKOKU, 12, 0x058B }, { SCENE_00KEIKOKU, 12, 0x0A14 },  { SCENE_00KEIKOKU, 12, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance13[] = {
    { SCENE_00KEIKOKU, 13, 0x0A14 },  { -SCENE_00KEIKOKU, 13, 0x0A14 }, { -SCENE_00KEIKOKU, 13, 0x0A14 },
    { -SCENE_00KEIKOKU, 13, 0x058B }, { SCENE_00KEIKOKU, 13, 0x0A14 },  { SCENE_00KEIKOKU, 13, 0x0A14 },
};

static MMEntranceTableEntry sTerminaFieldEntrance14[] = {
    { SCENE_00KEIKOKU, 14, 0x858B },
};

static MMEntranceTableEntry* sTerminaFieldEntranceTable[] = {
    sTerminaFieldEntrance0,  sTerminaFieldEntrance1,  sTerminaFieldEntrance2,  sTerminaFieldEntrance3,
    sTerminaFieldEntrance4,  sTerminaFieldEntrance5,  sTerminaFieldEntrance6,  sTerminaFieldEntrance7,
    sTerminaFieldEntrance8,  sTerminaFieldEntrance9,  sTerminaFieldEntrance10, sTerminaFieldEntrance11,
    sTerminaFieldEntrance12, sTerminaFieldEntrance13, sTerminaFieldEntrance14,
};

static MMEntranceTableEntry sPostOfficeEntrance0[] = {
    { SCENE_POSTHOUSE, 0, 0x4102 },
};

static MMEntranceTableEntry* sPostOfficeEntranceTable[] = {
    sPostOfficeEntrance0,
};

static MMEntranceTableEntry sMarineResearchLabEntrance0[] = {
    { SCENE_LABO, 0, 0x4102 },
};

static MMEntranceTableEntry* sMarineResearchLabEntranceTable[] = {
    sMarineResearchLabEntrance0,
};

static MMEntranceTableEntry sDampesHouseEntrance0[] = {
    { SCENE_DANPEI2TEST, 0, 0x4102 },
};

static MMEntranceTableEntry sDampesHouseEntrance1[] = {
    { SCENE_DANPEI2TEST, 1, 0x0102 },
};

static MMEntranceTableEntry* sDampesHouseEntranceTable[] = {
    sDampesHouseEntrance0,
    sDampesHouseEntrance1,
};

static MMEntranceTableEntry sGoronShrineEntrance0[] = {
    { SCENE_16GORON_HOUSE, 0, 0x4102 },
    { SCENE_16GORON_HOUSE, 0, 0x4102 },
};

static MMEntranceTableEntry sGoronShrineEntrance1[] = {
    { SCENE_16GORON_HOUSE, 1, 0x0102 },
    { SCENE_16GORON_HOUSE, 1, 0x0102 },
};

static MMEntranceTableEntry sGoronShrineEntrance2[] = {
    { SCENE_16GORON_HOUSE, 2, 0x058B },
    { SCENE_16GORON_HOUSE, 2, 0x058B },
};

static MMEntranceTableEntry sGoronShrineEntrance3[] = {
    { SCENE_16GORON_HOUSE, 3, 0x0102 },
    { SCENE_16GORON_HOUSE, 3, 0x0102 },
};

static MMEntranceTableEntry* sGoronShrineEntranceTable[] = {
    sGoronShrineEntrance0,
    sGoronShrineEntrance1,
    sGoronShrineEntrance2,
    sGoronShrineEntrance3,
};

static MMEntranceTableEntry sZoraHallEntrance0[] = {
    { SCENE_33ZORACITY, 0, 0x4993 },
    { SCENE_33ZORACITY, 0, 0x8102 },
};

static MMEntranceTableEntry sZoraHallEntrance1[] = {
    { SCENE_33ZORACITY, 1, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance2[] = {
    { SCENE_33ZORACITY, 2, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance3[] = {
    { SCENE_33ZORACITY, 3, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance4[] = {
    { SCENE_33ZORACITY, 4, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance5[] = {
    { SCENE_33ZORACITY, 5, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance6[] = {
    { SCENE_33ZORACITY, 6, 0x4102 },
};

static MMEntranceTableEntry sZoraHallEntrance7[] = {
    { SCENE_33ZORACITY, 7, 0x058B },
};

static MMEntranceTableEntry sZoraHallEntrance8[] = {
    { SCENE_33ZORACITY, 8, 0x8183 },
};

static MMEntranceTableEntry* sZoraHallEntranceTable[] = {
    sZoraHallEntrance0, sZoraHallEntrance1, sZoraHallEntrance2, sZoraHallEntrance3, sZoraHallEntrance4,
    sZoraHallEntrance5, sZoraHallEntrance6, sZoraHallEntrance7, sZoraHallEntrance8,
};

static MMEntranceTableEntry sTradingPostEntrance0[] = {
    { SCENE_8ITEMSHOP, 0, 0x4102 },
};

static MMEntranceTableEntry sTradingPostEntrance1[] = {
    { SCENE_8ITEMSHOP, 1, 0x0102 },
};

static MMEntranceTableEntry* sTradingPostEntranceTable[] = {
    sTradingPostEntrance0,
    sTradingPostEntrance1,
};

static MMEntranceTableEntry sRomaniRanchEntrance0[] = {
    { SCENE_F01, 0, 0x4A14 }, { SCENE_F01, 0, 0x0A14 }, { SCENE_F01, 0, 0x8102 }, { SCENE_F01, 0, 0x858B },
    { SCENE_F01, 0, 0x858B }, { SCENE_F01, 0, 0x0102 }, { SCENE_F01, 0, 0x8102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance1[] = {
    { SCENE_F01, 1, 0x0A14 },
};

static MMEntranceTableEntry sRomaniRanchEntrance2[] = {
    { SCENE_F01, 2, 0x0102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance3[] = {
    { SCENE_F01, 3, 0x0102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance4[] = {
    { SCENE_F01, 4, 0x8102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance5[] = {
    { SCENE_F01, 5, 0x8102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance6[] = {
    { SCENE_F01, 6, 0x0A14 },
};

static MMEntranceTableEntry sRomaniRanchEntrance7[] = {
    { SCENE_F01, 7, 0x0A14 },
};

static MMEntranceTableEntry sRomaniRanchEntrance8[] = {
    { SCENE_F01, 8, 0x0A14 },
};

static MMEntranceTableEntry sRomaniRanchEntrance9[] = {
    { SCENE_F01, 9, 0x0102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance10[] = {
    { SCENE_F01, 10, 0x0102 },
};

static MMEntranceTableEntry sRomaniRanchEntrance11[] = {
    { SCENE_F01, 11, 0x0102 },
};

static MMEntranceTableEntry* sRomaniRanchEntranceTable[] = {
    sRomaniRanchEntrance0, sRomaniRanchEntrance1, sRomaniRanchEntrance2,  sRomaniRanchEntrance3,
    sRomaniRanchEntrance4, sRomaniRanchEntrance5, sRomaniRanchEntrance6,  sRomaniRanchEntrance7,
    sRomaniRanchEntrance8, sRomaniRanchEntrance9, sRomaniRanchEntrance10, sRomaniRanchEntrance11,
};

static MMEntranceTableEntry sTwinmoldsLairEntrance0[] = {
    { -SCENE_INISIE_BS, 0, 0x0102 },
};

static MMEntranceTableEntry sTwinmoldsLairEntrance1[] = {
    { -SCENE_INISIE_BS, 1, 0x0102 },
};

static MMEntranceTableEntry sTwinmoldsLairEntrance2[] = {
    { -SCENE_INISIE_BS, 2, 0x0102 },
};

static MMEntranceTableEntry sTwinmoldsLairEntrance3[] = {
    { -SCENE_INISIE_BS, 3, 0x0102 },
};

static MMEntranceTableEntry sTwinmoldsLairEntrance4[] = {
    { -SCENE_INISIE_BS, 4, 0x0102 },
};

static MMEntranceTableEntry* sTwinmoldsLairEntranceTable[] = {
    sTwinmoldsLairEntrance0, sTwinmoldsLairEntrance1, sTwinmoldsLairEntrance2,
    sTwinmoldsLairEntrance3, sTwinmoldsLairEntrance4,
};

static MMEntranceTableEntry sGreatBayCoastEntrance0[] = {
    { SCENE_30GYOSON, 0, 0xCA14 },
    { SCENE_30GYOSON, 0, 0xCA14 },
    { SCENE_30GYOSON, 0, 0x8102 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance1[] = {
    { SCENE_30GYOSON, 1, 0xCA14 },
    { SCENE_30GYOSON, 1, 0xCA14 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance2[] = {
    { SCENE_30GYOSON, 2, 0x4993 },
    { SCENE_30GYOSON, 2, 0x4993 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance3[] = {
    { SCENE_30GYOSON, 3, 0x4A14 },
    { SCENE_30GYOSON, 3, 0x4A14 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance4[] = {
    { SCENE_30GYOSON, 4, 0x4102 },
    { SCENE_30GYOSON, 4, 0x4102 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance5[] = {
    { SCENE_30GYOSON, 5, 0x4993 },
    { SCENE_30GYOSON, 5, 0x4993 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance6[] = {
    { SCENE_30GYOSON, 6, 0x4993 },
    { SCENE_30GYOSON, 6, 0x4993 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance7[] = {
    { SCENE_30GYOSON, 7, 0x4102 },
    { SCENE_30GYOSON, 7, 0x4102 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance8[] = {
    { SCENE_30GYOSON, 8, 0x4102 },
    { SCENE_30GYOSON, 8, 0x4102 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance9[] = {
    { SCENE_30GYOSON, 9, 0x058B },
    { SCENE_30GYOSON, 9, 0x058B },
};

static MMEntranceTableEntry sGreatBayCoastEntrance10[] = {
    { SCENE_30GYOSON, 10, 0x858B },
    { SCENE_30GYOSON, 10, 0x858B },
};

static MMEntranceTableEntry sGreatBayCoastEntrance11[] = {
    { SCENE_30GYOSON, 11, 0x0A14 },
    { SCENE_30GYOSON, 11, 0x0A14 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance12[] = {
    { SCENE_30GYOSON, 12, 0x0A14 },
    { SCENE_30GYOSON, 12, 0x0A14 },
};

static MMEntranceTableEntry sGreatBayCoastEntrance13[] = {
    { SCENE_30GYOSON, 13, 0x0A14 },
    { SCENE_30GYOSON, 13, 0x0A14 },
};

static MMEntranceTableEntry* sGreatBayCoastEntranceTable[] = {
    sGreatBayCoastEntrance0,  sGreatBayCoastEntrance1,  sGreatBayCoastEntrance2,  sGreatBayCoastEntrance3,
    sGreatBayCoastEntrance4,  sGreatBayCoastEntrance5,  sGreatBayCoastEntrance6,  sGreatBayCoastEntrance7,
    sGreatBayCoastEntrance8,  sGreatBayCoastEntrance9,  sGreatBayCoastEntrance10, sGreatBayCoastEntrance11,
    sGreatBayCoastEntrance12, sGreatBayCoastEntrance13,
};

static MMEntranceTableEntry sZoraCapeEntrance0[] = {
    { SCENE_31MISAKI, 0, 0x8A14 },
    { SCENE_31MISAKI, 0, 0x8A14 },
};

static MMEntranceTableEntry sZoraCapeEntrance1[] = {
    { SCENE_31MISAKI, 1, 0x4993 },
    { SCENE_31MISAKI, 1, 0x4993 },
};

static MMEntranceTableEntry sZoraCapeEntrance2[] = {
    { SCENE_31MISAKI, 2, 0x4102 },
    { SCENE_31MISAKI, 2, 0x4102 },
};

static MMEntranceTableEntry sZoraCapeEntrance3[] = {
    { SCENE_31MISAKI, 3, 0x0993 },
    { SCENE_31MISAKI, 3, 0x0993 },
};

static MMEntranceTableEntry sZoraCapeEntrance4[] = {
    { SCENE_31MISAKI, 4, 0x4102 },
    { SCENE_31MISAKI, 4, 0x4102 },
};

static MMEntranceTableEntry sZoraCapeEntrance5[] = {
    { SCENE_31MISAKI, 5, 0x0102 },
    { SCENE_31MISAKI, 5, 0x0102 },
};

static MMEntranceTableEntry sZoraCapeEntrance6[] = {
    { SCENE_31MISAKI, 6, 0x0A14 },
    { SCENE_31MISAKI, 6, 0x0A14 },
};

static MMEntranceTableEntry sZoraCapeEntrance7[] = {
    { SCENE_31MISAKI, 7, 0x0A14 },
    { SCENE_31MISAKI, 7, 0x0A14 },
};

static MMEntranceTableEntry sZoraCapeEntrance8[] = {
    { SCENE_31MISAKI, 8, 0x0A14 },
    { SCENE_31MISAKI, 8, 0x0A14 },
};

static MMEntranceTableEntry sZoraCapeEntrance9[] = {
    { SCENE_31MISAKI, 9, 0x0A14 },
    { SCENE_31MISAKI, 9, 0x0A14 },
};

static MMEntranceTableEntry* sZoraCapeEntranceTable[] = {
    sZoraCapeEntrance0, sZoraCapeEntrance1, sZoraCapeEntrance2, sZoraCapeEntrance3, sZoraCapeEntrance4,
    sZoraCapeEntrance5, sZoraCapeEntrance6, sZoraCapeEntrance7, sZoraCapeEntrance8, sZoraCapeEntrance9,
};

static MMEntranceTableEntry sLotteryShopEntrance0[] = {
    { SCENE_TAKARAKUJI, 0, 0x4102 },
};

static MMEntranceTableEntry* sLotteryShopEntranceTable[] = {
    sLotteryShopEntrance0,
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance0[] = {
    { SCENE_TORIDE, 0, 0x4993 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance1[] = {
    { SCENE_TORIDE, 1, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance2[] = {
    { SCENE_TORIDE, 2, 0x8993 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance3[] = {
    { SCENE_TORIDE, 3, 0x8993 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance4[] = {
    { SCENE_TORIDE, 4, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance5[] = {
    { SCENE_TORIDE, 5, 0x8102 },
};

static MMEntranceTableEntry sPiratesFortressExteriorEntrance6[] = {
    { SCENE_TORIDE, 6, 0x8102 },
};

static MMEntranceTableEntry* sPiratesFortressExteriorEntranceTable[] = {
    sPiratesFortressExteriorEntrance0, sPiratesFortressExteriorEntrance1, sPiratesFortressExteriorEntrance2,
    sPiratesFortressExteriorEntrance3, sPiratesFortressExteriorEntrance4, sPiratesFortressExteriorEntrance5,
    sPiratesFortressExteriorEntrance6,
};

static MMEntranceTableEntry sFishermansHutEntrance0[] = {
    { SCENE_FISHERMAN, 0, 0x4102 },
};

static MMEntranceTableEntry* sFishermansHutEntranceTable[] = {
    sFishermansHutEntrance0,
};

static MMEntranceTableEntry sGoronShopEntrance0[] = {
    { SCENE_GORONSHOP, 0, 0x4102 },
};

static MMEntranceTableEntry* sGoronShopEntranceTable[] = {
    sGoronShopEntrance0,
};

static MMEntranceTableEntry sDekuKingsChamberEntrance0[] = {
    { -SCENE_DEKU_KING, 0, 0xC102 },
    { -SCENE_DEKU_KING, 0, 0x8102 },
};

static MMEntranceTableEntry sDekuKingsChamberEntrance1[] = {
    { -SCENE_DEKU_KING, 1, 0xC102 },
};

static MMEntranceTableEntry sDekuKingsChamberEntrance2[] = {
    { -SCENE_DEKU_KING, 2, 0x858B },
};

static MMEntranceTableEntry sDekuKingsChamberEntrance3[] = {
    { -SCENE_DEKU_KING, 3, 0x0102 },
};

static MMEntranceTableEntry* sDekuKingsChamberEntranceTable[] = {
    sDekuKingsChamberEntrance0,
    sDekuKingsChamberEntrance1,
    sDekuKingsChamberEntrance2,
    sDekuKingsChamberEntrance3,
};

static MMEntranceTableEntry sMoonGoronTrialEntrance0[] = {
    { -SCENE_LAST_GORON, 0, 0x0387 },
};

static MMEntranceTableEntry* sMoonGoronTrialEntranceTable[] = {
    sMoonGoronTrialEntrance0,
};

static MMEntranceTableEntry sRoadToSouthernSwampEntrance0[] = {
    { SCENE_24KEMONOMITI, 0, 0x8A14 },
};

static MMEntranceTableEntry sRoadToSouthernSwampEntrance1[] = {
    { SCENE_24KEMONOMITI, 1, 0x8A14 },
};

static MMEntranceTableEntry sRoadToSouthernSwampEntrance2[] = {
    { SCENE_24KEMONOMITI, 2, 0x0102 },
};

static MMEntranceTableEntry* sRoadToSouthernSwampEntranceTable[] = {
    sRoadToSouthernSwampEntrance0,
    sRoadToSouthernSwampEntrance1,
    sRoadToSouthernSwampEntrance2,
};

static MMEntranceTableEntry sDoggyRacetrackEntrance0[] = {
    { SCENE_F01_B, 0, 0xC102 },
};

static MMEntranceTableEntry sDoggyRacetrackEntrance1[] = {
    { SCENE_F01_B, 1, 0x0A14 },
};

static MMEntranceTableEntry* sDoggyRacetrackEntranceTable[] = {
    sDoggyRacetrackEntrance0,
    sDoggyRacetrackEntrance1,
};

static MMEntranceTableEntry sCuccoShackEntrance0[] = {
    { SCENE_F01C, 0, 0xC102 },
    { SCENE_F01C, 0, 0x8102 },
};

static MMEntranceTableEntry sCuccoShackEntrance1[] = {
    { SCENE_F01C, 1, 0x0A14 },
};

static MMEntranceTableEntry* sCuccoShackEntranceTable[] = {
    sCuccoShackEntrance0,
    sCuccoShackEntrance1,
};

static MMEntranceTableEntry sIkanaGraveyardEntrance0[] = {
    { SCENE_BOTI, 0, 0x4A14 },
    { SCENE_BOTI, 0, 0x8102 },
};

static MMEntranceTableEntry sIkanaGraveyardEntrance1[] = {
    { SCENE_BOTI, 1, 0x4102 },
};

static MMEntranceTableEntry sIkanaGraveyardEntrance2[] = {
    { SCENE_BOTI, 2, 0x4102 },
};

static MMEntranceTableEntry sIkanaGraveyardEntrance3[] = {
    { SCENE_BOTI, 3, 0x4102 },
};

static MMEntranceTableEntry sIkanaGraveyardEntrance4[] = {
    { SCENE_BOTI, 4, 0x4102 },
};

static MMEntranceTableEntry sIkanaGraveyardEntrance5[] = {
    { SCENE_BOTI, 5, 0x058B },
};

static MMEntranceTableEntry* sIkanaGraveyardEntranceTable[] = {
    sIkanaGraveyardEntrance0, sIkanaGraveyardEntrance1, sIkanaGraveyardEntrance2,
    sIkanaGraveyardEntrance3, sIkanaGraveyardEntrance4, sIkanaGraveyardEntrance5,
};

static MMEntranceTableEntry sGohtsLairEntrance0[] = {
    { -SCENE_HAKUGIN_BS, 0, 0x8102 },
};

static MMEntranceTableEntry* sGohtsLairEntranceTable[] = {
    sGohtsLairEntrance0,
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance0[] = {
    { SCENE_20SICHITAI, 0, 0xCA14 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance1[] = {
    { SCENE_20SICHITAI, 1, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance2[] = {
    { SCENE_20SICHITAI, 2, 0xC102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance3[] = {
    { SCENE_20SICHITAI, 3, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance4[] = {
    { SCENE_20SICHITAI, 4, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance5[] = {
    { SCENE_20SICHITAI, 5, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance6[] = {
    { SCENE_20SICHITAI, 6, 0x0102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance7[] = {
    { SCENE_20SICHITAI, 7, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance8[] = {
    { SCENE_20SICHITAI, 8, 0x4102 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance9[] = {
    { SCENE_20SICHITAI, 9, 0x4A14 },
};

static MMEntranceTableEntry sSouthernSwampPoisonedEntrance10[] = {
    { SCENE_20SICHITAI, 10, 0x4A14 },
};

static MMEntranceTableEntry* sSouthernSwampPoisonedEntranceTable[] = {
    sSouthernSwampPoisonedEntrance0, sSouthernSwampPoisonedEntrance1,  sSouthernSwampPoisonedEntrance2,
    sSouthernSwampPoisonedEntrance3, sSouthernSwampPoisonedEntrance4,  sSouthernSwampPoisonedEntrance5,
    sSouthernSwampPoisonedEntrance6, sSouthernSwampPoisonedEntrance7,  sSouthernSwampPoisonedEntrance8,
    sSouthernSwampPoisonedEntrance9, sSouthernSwampPoisonedEntrance10,
};

static MMEntranceTableEntry sWoodfallEntrance0[] = {
    { SCENE_21MITURINMAE, 0, 0xC102 },
    { SCENE_21MITURINMAE, 0, 0x0183 },
    { SCENE_21MITURINMAE, 0, 0xC102 },
};

static MMEntranceTableEntry sWoodfallEntrance1[] = {
    { SCENE_21MITURINMAE, 1, 0x4102 },
    { SCENE_21MITURINMAE, 1, 0x0183 },
    { SCENE_21MITURINMAE, 1, 0x4102 },
};

static MMEntranceTableEntry sWoodfallEntrance2[] = {
    { SCENE_21MITURINMAE, 2, 0x4102 },
    { SCENE_21MITURINMAE, 2, 0x0183 },
    { SCENE_21MITURINMAE, 2, 0x4102 },
};

static MMEntranceTableEntry sWoodfallEntrance3[] = {
    { SCENE_21MITURINMAE, 3, 0x4102 },
    { SCENE_21MITURINMAE, 3, 0x0183 },
    { SCENE_21MITURINMAE, 3, 0x4102 },
};

static MMEntranceTableEntry sWoodfallEntrance4[] = {
    { SCENE_21MITURINMAE, 4, 0x4102 },
    { SCENE_21MITURINMAE, 4, 0x0183 },
    { SCENE_21MITURINMAE, 4, 0x4102 },
};

static MMEntranceTableEntry* sWoodfallEntranceTable[] = {
    sWoodfallEntrance0, sWoodfallEntrance1, sWoodfallEntrance2, sWoodfallEntrance3, sWoodfallEntrance4,
};

static MMEntranceTableEntry sMoonZoraTrialEntrance0[] = {
    { -SCENE_LAST_ZORA, 0, 0x0387 },
};

static MMEntranceTableEntry sMoonZoraTrialEntrance1[] = {
    { -SCENE_LAST_ZORA, 1, 0x0102 },
};

static MMEntranceTableEntry* sMoonZoraTrialEntranceTable[] = {
    sMoonZoraTrialEntrance0,
    sMoonZoraTrialEntrance1,
};

static MMEntranceTableEntry sGoronVillageSpringEntrance0[] = {
    { SCENE_11GORONNOSATO2, 0, 0xC102 },
    { SCENE_11GORONNOSATO2, 0, 0x8102 },
};

static MMEntranceTableEntry sGoronVillageSpringEntrance1[] = {
    { SCENE_11GORONNOSATO2, 1, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageSpringEntrance2[] = {
    { SCENE_11GORONNOSATO2, 2, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageSpringEntrance3[] = {
    { SCENE_11GORONNOSATO2, 3, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageSpringEntrance4[] = {
    { SCENE_11GORONNOSATO2, 4, 0x0A14 },
};

static MMEntranceTableEntry* sGoronVillageSpringEntranceTable[] = {
    sGoronVillageSpringEntrance0, sGoronVillageSpringEntrance1, sGoronVillageSpringEntrance2,
    sGoronVillageSpringEntrance3, sGoronVillageSpringEntrance4,
};

static MMEntranceTableEntry sGreatBayTempleEntrance0[] = {
    { -SCENE_SEA, 0, 0x4102 },
};

static MMEntranceTableEntry sGreatBayTempleEntrance1[] = {
    { -SCENE_SEA, 1, 0x0102 },
};

static MMEntranceTableEntry sGreatBayTempleEntrance2[] = {
    { -SCENE_SEA, 2, 0x0102 },
};

static MMEntranceTableEntry* sGreatBayTempleEntranceTable[] = {
    sGreatBayTempleEntrance0,
    sGreatBayTempleEntrance1,
    sGreatBayTempleEntrance2,
};

static MMEntranceTableEntry sWaterfallRapidsEntrance0[] = {
    { SCENE_35TAKI, 0, 0x4102 },
};

static MMEntranceTableEntry sWaterfallRapidsEntrance1[] = {
    { SCENE_35TAKI, 1, 0x0A14 },
};

static MMEntranceTableEntry sWaterfallRapidsEntrance2[] = {
    { SCENE_35TAKI, 2, 0x0A14 },
};

static MMEntranceTableEntry sWaterfallRapidsEntrance3[] = {
    { SCENE_35TAKI, 3, 0x0A14 },
};

static MMEntranceTableEntry* sWaterfallRapidsEntranceTable[] = {
    sWaterfallRapidsEntrance0,
    sWaterfallRapidsEntrance1,
    sWaterfallRapidsEntrance2,
    sWaterfallRapidsEntrance3,
};

static MMEntranceTableEntry sBeneathTheWellEntrance0[] = {
    { -SCENE_REDEAD, 0, 0x4102 },
};

static MMEntranceTableEntry sBeneathTheWellEntrance1[] = {
    { -SCENE_REDEAD, 1, 0x4102 },
};

static MMEntranceTableEntry* sBeneathTheWellEntranceTable[] = {
    sBeneathTheWellEntrance0,
    sBeneathTheWellEntrance1,
};

static MMEntranceTableEntry sZoraHallRoomsEntrance0[] = {
    { SCENE_BANDROOM, 0, 0x0102 },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance1[] = {
    { SCENE_BANDROOM, 1, 0x0102 },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance2[] = {
    { SCENE_BANDROOM, 2, 0x0102 },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance3[] = {
    { SCENE_BANDROOM, 3, 0x0102 },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance4[] = {
    { SCENE_BANDROOM, 4, 0x858B },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance5[] = {
    { SCENE_BANDROOM, 5, 0x0102 },
};

static MMEntranceTableEntry sZoraHallRoomsEntrance6[] = {
    { SCENE_BANDROOM, 6, 0x0102 },
};

static MMEntranceTableEntry* sZoraHallRoomsEntranceTable[] = {
    sZoraHallRoomsEntrance0, sZoraHallRoomsEntrance1, sZoraHallRoomsEntrance2, sZoraHallRoomsEntrance3,
    sZoraHallRoomsEntrance4, sZoraHallRoomsEntrance5, sZoraHallRoomsEntrance6,
};

static MMEntranceTableEntry sGoronVillageWinterEntrance0[] = {
    { SCENE_11GORONNOSATO, 0, 0xC102 },
};

static MMEntranceTableEntry sGoronVillageWinterEntrance1[] = {
    { SCENE_11GORONNOSATO, 1, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageWinterEntrance2[] = {
    { SCENE_11GORONNOSATO, 2, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageWinterEntrance3[] = {
    { SCENE_11GORONNOSATO, 3, 0x4102 },
};

static MMEntranceTableEntry sGoronVillageWinterEntrance4[] = {
    { SCENE_11GORONNOSATO, 4, 0x0A14 },
};

static MMEntranceTableEntry* sGoronVillageWinterEntranceTable[] = {
    sGoronVillageWinterEntrance0, sGoronVillageWinterEntrance1, sGoronVillageWinterEntrance2,
    sGoronVillageWinterEntrance3, sGoronVillageWinterEntrance4,
};

static MMEntranceTableEntry sGoronGraveryardEntrance0[] = {
    { SCENE_GORON_HAKA, 0, 0x4102 },
};

static MMEntranceTableEntry sGoronGraveryardEntrance1[] = {
    { SCENE_GORON_HAKA, 1, 0x058B },
};

static MMEntranceTableEntry* sGoronGraveryardEntranceTable[] = {
    sGoronGraveryardEntrance0,
    sGoronGraveryardEntrance1,
};

static MMEntranceTableEntry sSakonsHideoutEntrance0[] = {
    { SCENE_SECOM, 0, 0x4102 },
};

static MMEntranceTableEntry* sSakonsHideoutEntranceTable[] = {
    sSakonsHideoutEntrance0,
};

static MMEntranceTableEntry sMountainVillageWinterEntrance0[] = {
    { SCENE_10YUKIYAMANOMURA, 0, 0x4A14 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance1[] = {
    { SCENE_10YUKIYAMANOMURA, 1, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance2[] = {
    { SCENE_10YUKIYAMANOMURA, 2, 0xCA14 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance3[] = {
    { SCENE_10YUKIYAMANOMURA, 3, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance4[] = {
    { SCENE_10YUKIYAMANOMURA, 4, 0xCA14 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance5[] = {
    { SCENE_10YUKIYAMANOMURA, 5, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance6[] = {
    { SCENE_10YUKIYAMANOMURA, 6, 0x4A14 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance7[] = {
    { SCENE_10YUKIYAMANOMURA, 7, 0x4A14 },
};

static MMEntranceTableEntry sMountainVillageWinterEntrance8[] = {
    { SCENE_10YUKIYAMANOMURA, 8, 0x4A14 },
};

static MMEntranceTableEntry* sMountainVillageWinterEntranceTable[] = {
    sMountainVillageWinterEntrance0, sMountainVillageWinterEntrance1, sMountainVillageWinterEntrance2,
    sMountainVillageWinterEntrance3, sMountainVillageWinterEntrance4, sMountainVillageWinterEntrance5,
    sMountainVillageWinterEntrance6, sMountainVillageWinterEntrance7, sMountainVillageWinterEntrance8,
};

static MMEntranceTableEntry sGhostHutEntrance0[] = {
    { SCENE_TOUGITES, 0, 0x4102 },
};

static MMEntranceTableEntry sGhostHutEntrance1[] = {
    { SCENE_TOUGITES, 1, 0x0102 },
};

static MMEntranceTableEntry sGhostHutEntrance2[] = {
    { SCENE_TOUGITES, 2, 0x0102 },
};

static MMEntranceTableEntry* sGhostHutEntranceTable[] = {
    sGhostHutEntrance0,
    sGhostHutEntrance1,
    sGhostHutEntrance2,
};

static MMEntranceTableEntry sDekuShrineEntrance0[] = {
    { SCENE_DANPEI, 0, 0x4102 },
};

static MMEntranceTableEntry sDekuShrineEntrance1[] = {
    { SCENE_DANPEI, 1, 0x0102 },
};

static MMEntranceTableEntry sDekuShrineEntrance2[] = {
    { SCENE_DANPEI, 2, 0x0102 },
};

static MMEntranceTableEntry* sDekuShrineEntranceTable[] = {
    sDekuShrineEntrance0,
    sDekuShrineEntrance1,
    sDekuShrineEntrance2,
};

static MMEntranceTableEntry sRoadToIkanaEntrance0[] = {
    { SCENE_IKANAMAE, 0, 0x8A14 },
};

static MMEntranceTableEntry sRoadToIkanaEntrance1[] = {
    { SCENE_IKANAMAE, 1, 0x8A14 },
};

static MMEntranceTableEntry sRoadToIkanaEntrance2[] = {
    { SCENE_IKANAMAE, 2, 0x0A14 },
};

static MMEntranceTableEntry* sRoadToIkanaEntranceTable[] = {
    sRoadToIkanaEntrance0,
    sRoadToIkanaEntrance1,
    sRoadToIkanaEntrance2,
};

static MMEntranceTableEntry sMusicBoxHouseEntrance0[] = {
    { SCENE_MUSICHOUSE, 0, 0x4102 },
};

static MMEntranceTableEntry* sMusicBoxHouseEntranceTable[] = {
    sMusicBoxHouseEntrance0,
};

static MMEntranceTableEntry sIgosDuIkanasLairEntrance0[] = {
    { -SCENE_IKNINSIDE, 0, 0x8102 },
    { -SCENE_IKNINSIDE, 0, 0x8102 },
};

static MMEntranceTableEntry* sIgosDuIkanasLairEntranceTable[] = {
    sIgosDuIkanasLairEntrance0,
};

static MMEntranceTableEntry sSwordmansSchoolEntrance0[] = {
    { SCENE_DOUJOU, 0, 0x4102 },
};

static MMEntranceTableEntry* sSwordmansSchoolEntranceTable[] = {
    sSwordmansSchoolEntrance0,
};

static MMEntranceTableEntry sTouristInformationEntrance0[] = {
    { SCENE_MAP_SHOP, 0, 0x4102 },
};

static MMEntranceTableEntry sTouristInformationEntrance1[] = {
    { SCENE_MAP_SHOP, 1, 0x0102 },
};

static MMEntranceTableEntry sTouristInformationEntrance2[] = {
    { SCENE_MAP_SHOP, 2, 0x0102 },
};

static MMEntranceTableEntry* sTouristInformationEntranceTable[] = {
    sTouristInformationEntrance0,
    sTouristInformationEntrance1,
    sTouristInformationEntrance2,
};

static MMEntranceTableEntry sStoneTowerEntrance0[] = {
    { SCENE_F40, 0, 0x4102 },
};

static MMEntranceTableEntry sStoneTowerEntrance1[] = {
    { SCENE_F40, 1, 0xCA14 },
};

static MMEntranceTableEntry sStoneTowerEntrance2[] = {
    { SCENE_F40, 2, 0xC102 },
};

static MMEntranceTableEntry sStoneTowerEntrance3[] = {
    { SCENE_F40, 3, 0x4A14 },
};

static MMEntranceTableEntry* sStoneTowerEntranceTable[] = {
    sStoneTowerEntrance0,
    sStoneTowerEntrance1,
    sStoneTowerEntrance2,
    sStoneTowerEntrance3,
};

static MMEntranceTableEntry sStoneTowerInvertedEntrance0[] = {
    { SCENE_F41, 0, 0x4A14 },
};

static MMEntranceTableEntry sStoneTowerInvertedEntrance1[] = {
    { SCENE_F41, 1, 0xC102 },
};

static MMEntranceTableEntry* sStoneTowerInvertedEntranceTable[] = {
    sStoneTowerInvertedEntrance0,
    sStoneTowerInvertedEntrance1,
};

static MMEntranceTableEntry sMountainVillageSpringEntrance0[] = {
    { SCENE_10YUKIYAMANOMURA2, 0, 0x4A14 },
    { SCENE_10YUKIYAMANOMURA2, 0, 0x4A14 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance1[] = {
    { SCENE_10YUKIYAMANOMURA2, 1, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance2[] = {
    { SCENE_10YUKIYAMANOMURA2, 2, 0xCA14 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance3[] = {
    { SCENE_10YUKIYAMANOMURA2, 3, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance4[] = {
    { SCENE_10YUKIYAMANOMURA2, 4, 0xCA14 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance5[] = {
    { SCENE_10YUKIYAMANOMURA2, 5, 0x4102 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance6[] = {
    { SCENE_10YUKIYAMANOMURA2, 6, 0xCA14 },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance7[] = {
    { SCENE_10YUKIYAMANOMURA2, 7, 0x458B },
};

static MMEntranceTableEntry sMountainVillageSpringEntrance8[] = {
    { SCENE_10YUKIYAMANOMURA2, 8, 0x4A14 },
};

static MMEntranceTableEntry* sMountainVillageSpringEntranceTable[] = {
    sMountainVillageSpringEntrance0, sMountainVillageSpringEntrance1, sMountainVillageSpringEntrance2,
    sMountainVillageSpringEntrance3, sMountainVillageSpringEntrance4, sMountainVillageSpringEntrance5,
    sMountainVillageSpringEntrance6, sMountainVillageSpringEntrance7, sMountainVillageSpringEntrance8,
};

static MMEntranceTableEntry sPathToSnowheadEntrance0[] = {
    { SCENE_14YUKIDAMANOMITI, 0, 0xCA14 },
    { SCENE_14YUKIDAMANOMITI, 0, 0xCA14 },
};

static MMEntranceTableEntry sPathToSnowheadEntrance1[] = {
    { SCENE_14YUKIDAMANOMITI, 1, 0xCA14 },
    { SCENE_14YUKIDAMANOMITI, 1, 0xCA14 },
};

static MMEntranceTableEntry* sPathToSnowheadEntranceTable[] = {
    sPathToSnowheadEntrance0,
    sPathToSnowheadEntrance1,
};

static MMEntranceTableEntry sSnowheadEntrance0[] = {
    { SCENE_12HAKUGINMAE, 0, 0xCA14 },
    { SCENE_12HAKUGINMAE, 0, 0xCA14 },
};

static MMEntranceTableEntry sSnowheadEntrance1[] = {
    { SCENE_12HAKUGINMAE, 1, 0x4102 },
    { SCENE_12HAKUGINMAE, 1, 0x4102 },
};

static MMEntranceTableEntry sSnowheadEntrance2[] = {
    { SCENE_12HAKUGINMAE, 2, 0x4102 },
    { SCENE_12HAKUGINMAE, 2, 0x4102 },
};

static MMEntranceTableEntry sSnowheadEntrance3[] = {
    { SCENE_12HAKUGINMAE, 3, 0x4102 },
    { SCENE_12HAKUGINMAE, 3, 0x4102 },
};

static MMEntranceTableEntry* sSnowheadEntranceTable[] = {
    sSnowheadEntrance0,
    sSnowheadEntrance1,
    sSnowheadEntrance2,
    sSnowheadEntrance3,
};

static MMEntranceTableEntry sPathToGoronVillageWinterEntrance0[] = {
    { SCENE_17SETUGEN, 0, 0x8A14 },
};

static MMEntranceTableEntry sPathToGoronVillageWinterEntrance1[] = {
    { SCENE_17SETUGEN, 1, 0x8102 },
};

static MMEntranceTableEntry sPathToGoronVillageWinterEntrance2[] = {
    { SCENE_17SETUGEN, 2, 0x0102 },
};

static MMEntranceTableEntry* sPathToGoronVillageWinterEntranceTable[] = {
    sPathToGoronVillageWinterEntrance0,
    sPathToGoronVillageWinterEntrance1,
    sPathToGoronVillageWinterEntrance2,
};

static MMEntranceTableEntry sPathToGoronVillageSpringEntrance0[] = {
    { SCENE_17SETUGEN2, 0, 0x8A14 },
};

static MMEntranceTableEntry sPathToGoronVillageSpringEntrance1[] = {
    { SCENE_17SETUGEN2, 1, 0x8102 },
};

static MMEntranceTableEntry sPathToGoronVillageSpringEntrance2[] = {
    { SCENE_17SETUGEN2, 2, 0x0102 },
};

static MMEntranceTableEntry* sPathToGoronVillageSpringEntranceTable[] = {
    sPathToGoronVillageSpringEntrance0,
    sPathToGoronVillageSpringEntrance1,
    sPathToGoronVillageSpringEntrance2,
};

static MMEntranceTableEntry sGyorgsLairEntrance0[] = {
    { -SCENE_SEA_BS, 0, 0x8102 },
};

static MMEntranceTableEntry sGyorgsLairEntrance1[] = {
    { -SCENE_SEA_BS, 1, 0x8102 },
};

static MMEntranceTableEntry* sGyorgsLairEntranceTable[] = {
    sGyorgsLairEntrance0,
    sGyorgsLairEntrance1,
};

static MMEntranceTableEntry sSecretShrineEntrance0[] = {
    { -SCENE_RANDOM, 0, 0x4102 },
};

static MMEntranceTableEntry* sSecretShrineEntranceTable[] = {
    sSecretShrineEntrance0,
};

static MMEntranceTableEntry sStockPotInnEntrance0[] = {
    { SCENE_YADOYA, 0, 0x4102 },
    { SCENE_YADOYA, 0, 0x8102 },
};

static MMEntranceTableEntry sStockPotInnEntrance1[] = {
    { SCENE_YADOYA, 1, 0x4102 },
};

static MMEntranceTableEntry sStockPotInnEntrance2[] = {
    { SCENE_YADOYA, 2, 0x0102 },
};

static MMEntranceTableEntry sStockPotInnEntrance3[] = {
    { SCENE_YADOYA, 3, 0x0102 },
};

static MMEntranceTableEntry sStockPotInnEntrance4[] = {
    { SCENE_YADOYA, 4, 0x0102 },
};

static MMEntranceTableEntry sStockPotInnEntrance5[] = {
    { SCENE_YADOYA, 5, 0x0102 },
};

static MMEntranceTableEntry* sStockPotInnEntranceTable[] = {
    sStockPotInnEntrance0, sStockPotInnEntrance1, sStockPotInnEntrance2,
    sStockPotInnEntrance3, sStockPotInnEntrance4, sStockPotInnEntrance5,
};

static MMEntranceTableEntry sGreatBayCutsceneEntrance0[] = {
    { SCENE_KONPEKI_ENT, 0, 0x4102 },
};

static MMEntranceTableEntry* sGreatBayCutsceneEntranceTable[] = {
    sGreatBayCutsceneEntrance0,
};

static MMEntranceTableEntry sClockTowerInteriorEntrance0[] = {
    { SCENE_INSIDETOWER, 0, 0x0102 },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance1[] = {
    { SCENE_INSIDETOWER, 1, 0x0102 },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance2[] = {
    { SCENE_INSIDETOWER, 2, 0x058B },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance3[] = {
    { SCENE_INSIDETOWER, 3, 0x0102 },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance4[] = {
    { SCENE_INSIDETOWER, 4, 0x058B },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance5[] = {
    { SCENE_INSIDETOWER, 5, 0x0102 },
};

static MMEntranceTableEntry sClockTowerInteriorEntrance6[] = {
    { SCENE_INSIDETOWER, 6, 0x858B },
};

static MMEntranceTableEntry* sClockTowerInteriorEntranceTable[] = {
    sClockTowerInteriorEntrance0, sClockTowerInteriorEntrance1, sClockTowerInteriorEntrance2,
    sClockTowerInteriorEntrance3, sClockTowerInteriorEntrance4, sClockTowerInteriorEntrance5,
    sClockTowerInteriorEntrance6,
};

static MMEntranceTableEntry sWoodsOfMysteryEntrance0[] = {
    { SCENE_26SARUNOMORI, 0, 0x4102 },
};

static MMEntranceTableEntry* sWoodsOfMysteryEntranceTable[] = {
    sWoodsOfMysteryEntrance0,
};

static MMEntranceTableEntry sLostWoodsEntrance0[] = {
    { -SCENE_LOST_WOODS, 0, 0x858B },
    { -SCENE_LOST_WOODS, 0, 0x8183 },
    { -SCENE_LOST_WOODS, 0, 0x858B },
    { -SCENE_LOST_WOODS, 0, 0x8102 },
};

static MMEntranceTableEntry sLostWoodsEntrance1[] = {
    { -SCENE_LOST_WOODS, 1, 0x058B },
    { -SCENE_LOST_WOODS, 1, 0x058B },
    { -SCENE_LOST_WOODS, 1, 0x058B },
    { -SCENE_LOST_WOODS, 1, 0x058B },
};

static MMEntranceTableEntry sLostWoodsEntrance2[] = {
    { -SCENE_LOST_WOODS, 2, 0x058B },
    { -SCENE_LOST_WOODS, 2, 0x058B },
    { -SCENE_LOST_WOODS, 2, 0x058B },
    { -SCENE_LOST_WOODS, 2, 0x058B },
};

static MMEntranceTableEntry* sLostWoodsEntranceTable[] = {
    sLostWoodsEntrance0,
    sLostWoodsEntrance1,
    sLostWoodsEntrance2,
};

static MMEntranceTableEntry sMoonLinkTrialEntrance0[] = {
    { SCENE_LAST_LINK, 0, 0x0387 },
};

static MMEntranceTableEntry* sMoonLinkTrialEntranceTable[] = {
    sMoonLinkTrialEntrance0,
};

static MMEntranceTableEntry sTheMoonEntrance0[] = {
    { SCENE_SOUGEN, 0, 0x0387 },
};

static MMEntranceTableEntry* sTheMoonEntranceTable[] = {
    sTheMoonEntrance0,
};

static MMEntranceTableEntry sBombShopEntrance0[] = {
    { SCENE_BOMYA, 0, 0x4102 },
};

static MMEntranceTableEntry sBombShopEntrance1[] = {
    { SCENE_BOMYA, 1, 0x0102 },
};

static MMEntranceTableEntry* sBombShopEntranceTable[] = {
    sBombShopEntrance0,
    sBombShopEntrance1,
};

static MMEntranceTableEntry sGiantsChamberEntrance0[] = {
    { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 },
    { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 },
    { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 },
    { SCENE_KYOJINNOMA, 0, 0x0102 }, { SCENE_KYOJINNOMA, 0, 0x0102 },
};

static MMEntranceTableEntry* sGiantsChamberEntranceTable[] = {
    sGiantsChamberEntrance0,
};

static MMEntranceTableEntry sGormanTrackEntrance0[] = {
    { SCENE_KOEPONARACE, 0, 0x4A14 },
};

static MMEntranceTableEntry sGormanTrackEntrance1[] = {
    { SCENE_KOEPONARACE, 1, 0x4A14 },
};

static MMEntranceTableEntry sGormanTrackEntrance2[] = {
    { SCENE_KOEPONARACE, 2, 0x4A14 },
};

static MMEntranceTableEntry sGormanTrackEntrance3[] = {
    { SCENE_KOEPONARACE, 3, 0x4A14 },
};

static MMEntranceTableEntry sGormanTrackEntrance4[] = {
    { SCENE_KOEPONARACE, 4, 0x0102 },
};

static MMEntranceTableEntry sGormanTrackEntrance5[] = {
    { SCENE_KOEPONARACE, 5, 0x0A14 },
};

static MMEntranceTableEntry* sGormanTrackEntranceTable[] = {
    sGormanTrackEntrance0, sGormanTrackEntrance1, sGormanTrackEntrance2,
    sGormanTrackEntrance3, sGormanTrackEntrance4, sGormanTrackEntrance5,
};

static MMEntranceTableEntry sGoronRacetrackEntrance0[] = {
    { SCENE_GORONRACE, 0, 0x4102 },
    { SCENE_GORONRACE, 0, 0x4102 },
};

static MMEntranceTableEntry sGoronRacetrackEntrance1[] = {
    { SCENE_GORONRACE, 1, 0x8A14 },
    { SCENE_GORONRACE, 1, 0x8A14 },
};

static MMEntranceTableEntry sGoronRacetrackEntrance2[] = {
    { SCENE_GORONRACE, 2, 0x0A14 },
    { SCENE_GORONRACE, 2, 0x0A14 },
};

static MMEntranceTableEntry* sGoronRacetrackEntranceTable[] = {
    sGoronRacetrackEntrance0,
    sGoronRacetrackEntrance1,
    sGoronRacetrackEntrance2,
};

static MMEntranceTableEntry sEastClockTownEntrance0[] = {
    { SCENE_TOWN, 0, 0x4102 },
    { SCENE_TOWN, 0, 0x8102 },
    { SCENE_TOWN, 0, 0x058B },
};

static MMEntranceTableEntry sEastClockTownEntrance1[] = {
    { SCENE_TOWN, 1, 0xCA14 },
};

static MMEntranceTableEntry sEastClockTownEntrance2[] = {
    { SCENE_TOWN, 2, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance3[] = {
    { SCENE_TOWN, 3, 0xC102 },
};

static MMEntranceTableEntry sEastClockTownEntrance4[] = {
    { SCENE_TOWN, 4, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance5[] = {
    { SCENE_TOWN, 5, 0xC102 },
};

static MMEntranceTableEntry sEastClockTownEntrance6[] = {
    { SCENE_TOWN, 6, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance7[] = {
    { SCENE_TOWN, 7, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance8[] = {
    { SCENE_TOWN, 8, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance9[] = {
    { SCENE_TOWN, 9, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance10[] = {
    { SCENE_TOWN, 10, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance11[] = {
    { SCENE_TOWN, 11, 0x4102 },
};

static MMEntranceTableEntry sEastClockTownEntrance12[] = {
    { SCENE_TOWN, 12, 0x4102 },
};

static MMEntranceTableEntry* sEastClockTownEntranceTable[] = {
    sEastClockTownEntrance0,  sEastClockTownEntrance1, sEastClockTownEntrance2,  sEastClockTownEntrance3,
    sEastClockTownEntrance4,  sEastClockTownEntrance5, sEastClockTownEntrance6,  sEastClockTownEntrance7,
    sEastClockTownEntrance8,  sEastClockTownEntrance9, sEastClockTownEntrance10, sEastClockTownEntrance11,
    sEastClockTownEntrance12,
};

static MMEntranceTableEntry sWestClockTownEntrance0[] = {
    { SCENE_ICHIBA, 0, 0x4102 },
    { SCENE_ICHIBA, 0, 0x8102 },
};

static MMEntranceTableEntry sWestClockTownEntrance1[] = {
    { SCENE_ICHIBA, 1, 0xC102 },
};

static MMEntranceTableEntry sWestClockTownEntrance2[] = {
    { SCENE_ICHIBA, 2, 0xCA14 },
};

static MMEntranceTableEntry sWestClockTownEntrance3[] = {
    { SCENE_ICHIBA, 3, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance4[] = {
    { SCENE_ICHIBA, 4, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance5[] = {
    { SCENE_ICHIBA, 5, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance6[] = {
    { SCENE_ICHIBA, 6, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance7[] = {
    { SCENE_ICHIBA, 7, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance8[] = {
    { SCENE_ICHIBA, 8, 0x4102 },
};

static MMEntranceTableEntry sWestClockTownEntrance9[] = {
    { SCENE_ICHIBA, 9, 0x4A14 },
};

static MMEntranceTableEntry* sWestClockTownEntranceTable[] = {
    sWestClockTownEntrance0, sWestClockTownEntrance1, sWestClockTownEntrance2, sWestClockTownEntrance3,
    sWestClockTownEntrance4, sWestClockTownEntrance5, sWestClockTownEntrance6, sWestClockTownEntrance7,
    sWestClockTownEntrance8, sWestClockTownEntrance9,
};

static MMEntranceTableEntry sNorthClockTownEntrance0[] = {
    { SCENE_BACKTOWN, 0, 0x4102 },
    { SCENE_BACKTOWN, 0, 0x458B },
};

static MMEntranceTableEntry sNorthClockTownEntrance1[] = {
    { SCENE_BACKTOWN, 1, 0xC102 },
};

static MMEntranceTableEntry sNorthClockTownEntrance2[] = {
    { SCENE_BACKTOWN, 2, 0xC102 },
};

static MMEntranceTableEntry sNorthClockTownEntrance3[] = {
    { SCENE_BACKTOWN, 3, 0x4102 },
};

static MMEntranceTableEntry sNorthClockTownEntrance4[] = {
    { SCENE_BACKTOWN, 4, 0x4102 },
};

static MMEntranceTableEntry sNorthClockTownEntrance5[] = {
    { SCENE_BACKTOWN, 5, 0x8A14 },
};

static MMEntranceTableEntry sNorthClockTownEntrance6[] = {
    { SCENE_BACKTOWN, 6, 0x8A14 },
};

static MMEntranceTableEntry sNorthClockTownEntrance7[] = {
    { SCENE_BACKTOWN, 7, 0x8A14 },
};

static MMEntranceTableEntry* sNorthClockTownEntranceTable[] = {
    sNorthClockTownEntrance0, sNorthClockTownEntrance1, sNorthClockTownEntrance2, sNorthClockTownEntrance3,
    sNorthClockTownEntrance4, sNorthClockTownEntrance5, sNorthClockTownEntrance6, sNorthClockTownEntrance7,
};

static MMEntranceTableEntry sSouthClockTownEntrance0[] = {
    { SCENE_CLOCKTOWER, 0, 0x4102 },
    { SCENE_CLOCKTOWER, 0, 0x8102 },
    { SCENE_CLOCKTOWER, 0, 0x0A14 },
    { SCENE_CLOCKTOWER, 0, 0x0102 },
};

static MMEntranceTableEntry sSouthClockTownEntrance1[] = {
    { SCENE_CLOCKTOWER, 1, 0x4102 },
    { SCENE_CLOCKTOWER, 1, 0x8102 },
};

static MMEntranceTableEntry sSouthClockTownEntrance2[] = {
    { SCENE_CLOCKTOWER, 2, 0xC102 },
};

static MMEntranceTableEntry sSouthClockTownEntrance3[] = {
    { SCENE_CLOCKTOWER, 3, 0xCA14 },
};

static MMEntranceTableEntry sSouthClockTownEntrance4[] = {
    { SCENE_CLOCKTOWER, 4, 0xC102 },
};

static MMEntranceTableEntry sSouthClockTownEntrance5[] = {
    { SCENE_CLOCKTOWER, 5, 0xC102 },
};

static MMEntranceTableEntry sSouthClockTownEntrance6[] = {
    { SCENE_CLOCKTOWER, 6, 0xCA14 },
};

static MMEntranceTableEntry sSouthClockTownEntrance7[] = {
    { SCENE_CLOCKTOWER, 7, 0xCA14 },
};

static MMEntranceTableEntry sSouthClockTownEntrance8[] = {
    { SCENE_CLOCKTOWER, 8, 0x4A14 },
};

static MMEntranceTableEntry sSouthClockTownEntrance9[] = {
    { SCENE_CLOCKTOWER, 9, 0x4A14 },
};

static MMEntranceTableEntry sSouthClockTownEntrance10[] = {
    { SCENE_CLOCKTOWER, 10, 0x058B },
};

static MMEntranceTableEntry* sSouthClockTownEntranceTable[] = {
    sSouthClockTownEntrance0, sSouthClockTownEntrance1, sSouthClockTownEntrance2,  sSouthClockTownEntrance3,
    sSouthClockTownEntrance4, sSouthClockTownEntrance5, sSouthClockTownEntrance6,  sSouthClockTownEntrance7,
    sSouthClockTownEntrance8, sSouthClockTownEntrance9, sSouthClockTownEntrance10,
};

static MMEntranceTableEntry sLaundryPoolEntrance0[] = {
    { SCENE_ALLEY, 0, 0xCA14 },
};

static MMEntranceTableEntry sLaundryPoolEntrance1[] = {
    { SCENE_ALLEY, 1, 0x4A14 },
};

static MMEntranceTableEntry sLaundryPoolEntrance2[] = {
    { SCENE_ALLEY, 2, 0x4102 },
};

static MMEntranceTableEntry* sLaundryPoolEntranceTable[] = {
    sLaundryPoolEntrance0,
    sLaundryPoolEntrance1,
    sLaundryPoolEntrance2,
};

static MMEntranceTableEntry sGrottosEntrance0[] = {
    { SCENE_KAKUSIANA, 0, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance1[] = {
    { SCENE_KAKUSIANA, 1, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance2[] = {
    { SCENE_KAKUSIANA, 2, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance3[] = {
    { SCENE_KAKUSIANA, 3, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance4[] = {
    { SCENE_KAKUSIANA, 4, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance5[] = {
    { SCENE_KAKUSIANA, 5, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance6[] = {
    { SCENE_KAKUSIANA, 6, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance7[] = {
    { SCENE_KAKUSIANA, SCENE_KAKUSIANA, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance8[] = {
    { SCENE_KAKUSIANA, 8, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance9[] = {
    { SCENE_KAKUSIANA, 9, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance10[] = {
    { SCENE_KAKUSIANA, 10, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance11[] = {
    { SCENE_KAKUSIANA, 11, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance12[] = {
    { SCENE_KAKUSIANA, 12, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance13[] = {
    { SCENE_KAKUSIANA, 13, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance14[] = {
    { SCENE_KAKUSIANA, 14, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance15[] = {
    { SCENE_KAKUSIANA, 15, 0x0102 },
};

static MMEntranceTableEntry sGrottosEntrance16[] = {
    { SCENE_KAKUSIANA, 16, 0x0102 },
};

static MMEntranceTableEntry* sGrottosEntranceTable[] = {
    sGrottosEntrance0,  sGrottosEntrance1,  sGrottosEntrance2,  sGrottosEntrance3,  sGrottosEntrance4,
    sGrottosEntrance5,  sGrottosEntrance6,  sGrottosEntrance7,  sGrottosEntrance8,  sGrottosEntrance9,
    sGrottosEntrance10, sGrottosEntrance11, sGrottosEntrance12, sGrottosEntrance13, sGrottosEntrance14,
    sGrottosEntrance15, sGrottosEntrance16,
};

static MMEntranceTableEntry sCutsceneEntrance0[] = {
    { -SCENE_SPOT00, 0, 0x0102 }, { -SCENE_SPOT00, 0, 0x0102 }, { -SCENE_SPOT00, 0, 0x8102 },
    { -SCENE_SPOT00, 0, 0x0102 }, { -SCENE_SPOT00, 0, 0x058B }, { -SCENE_SPOT00, 0, 0x058B },
    { -SCENE_SPOT00, 0, 0x058B }, { -SCENE_SPOT00, 0, 0x058B }, { -SCENE_SPOT00, 0, 0x0183 },
    { -SCENE_SPOT00, 0, 0x0183 }, { -SCENE_SPOT00, 0, 0x8102 }, { -SCENE_SPOT00, 0, 0x0102 },
};

static MMEntranceTableEntry sCutsceneEntrance1[] = {
    { -SCENE_SPOT00, 1, 0x0183 }, { -SCENE_SPOT00, 1, 0x0102 }, { -SCENE_SPOT00, 1, 0x8102 },
    { -SCENE_SPOT00, 1, 0x0102 }, { -SCENE_SPOT00, 1, 0x8102 }, { -SCENE_SPOT00, 1, 0x058B },
    { -SCENE_SPOT00, 1, 0x058B }, { -SCENE_SPOT00, 1, 0x058B }, { -SCENE_SPOT00, 1, 0x058B },
    { -SCENE_SPOT00, 1, 0x8102 }, { -SCENE_SPOT00, 1, 0x8102 }, { -SCENE_SPOT00, 1, 0x0102 },
};

static MMEntranceTableEntry sCutsceneEntrance2[] = {
    { -SCENE_SPOT00, 2, 0x0183 }, { -SCENE_SPOT00, 2, 0x0102 }, { -SCENE_SPOT00, 2, 0x8102 },
    { -SCENE_SPOT00, 2, 0x0102 }, { -SCENE_SPOT00, 2, 0x8102 }, { -SCENE_SPOT00, 2, 0x058B },
    { -SCENE_SPOT00, 2, 0x058B }, { -SCENE_SPOT00, 2, 0x058B }, { -SCENE_SPOT00, 2, 0x058B },
    { -SCENE_SPOT00, 2, 0x858B }, { -SCENE_SPOT00, 2, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance3[] = {
    { -SCENE_SPOT00, 3, 0x0183 }, { -SCENE_SPOT00, 3, 0x0102 }, { -SCENE_SPOT00, 3, 0x8102 },
    { -SCENE_SPOT00, 3, 0x0102 }, { -SCENE_SPOT00, 3, 0x058B }, { -SCENE_SPOT00, 3, 0x058B },
    { -SCENE_SPOT00, 3, 0x058B }, { -SCENE_SPOT00, 3, 0x058B }, { -SCENE_SPOT00, 3, 0x058B },
    { -SCENE_SPOT00, 3, 0x058B }, { -SCENE_SPOT00, 3, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance4[] = {
    { -SCENE_SPOT00, 4, 0x0183 }, { -SCENE_SPOT00, 4, 0x0102 }, { -SCENE_SPOT00, 4, 0x8102 },
    { -SCENE_SPOT00, 4, 0x0102 }, { -SCENE_SPOT00, 4, 0x058B }, { -SCENE_SPOT00, 4, 0x058B },
    { -SCENE_SPOT00, 4, 0x058B }, { -SCENE_SPOT00, 4, 0x058B }, { -SCENE_SPOT00, 4, 0x058B },
    { -SCENE_SPOT00, 4, 0x058B }, { -SCENE_SPOT00, 4, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance5[] = {
    { -SCENE_SPOT00, 5, 0x0183 }, { -SCENE_SPOT00, 5, 0x0102 }, { -SCENE_SPOT00, 5, 0x8102 },
    { -SCENE_SPOT00, 5, 0x0102 }, { -SCENE_SPOT00, 5, 0x058B }, { -SCENE_SPOT00, 5, 0x058B },
    { -SCENE_SPOT00, 5, 0x058B }, { -SCENE_SPOT00, 5, 0x058B }, { -SCENE_SPOT00, 5, 0x058B },
    { -SCENE_SPOT00, 5, 0x858B }, { -SCENE_SPOT00, 5, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance6[] = {
    { -SCENE_SPOT00, 6, 0x0183 }, { -SCENE_SPOT00, 6, 0x0102 }, { -SCENE_SPOT00, 6, 0x8102 },
    { -SCENE_SPOT00, 6, 0x0102 }, { -SCENE_SPOT00, 6, 0x058B }, { -SCENE_SPOT00, 6, 0x058B },
    { -SCENE_SPOT00, 6, 0x058B }, { -SCENE_SPOT00, 6, 0x058B }, { -SCENE_SPOT00, 6, 0x058B },
    { -SCENE_SPOT00, 6, 0x858B }, { -SCENE_SPOT00, 6, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance7[] = {
    { -SCENE_SPOT00, 7, 0x0183 }, { -SCENE_SPOT00, 7, 0x0102 }, { -SCENE_SPOT00, 7, 0x8102 },
    { -SCENE_SPOT00, 7, 0x0102 }, { -SCENE_SPOT00, 7, 0x058B }, { -SCENE_SPOT00, 7, 0x058B },
    { -SCENE_SPOT00, 7, 0x058B }, { -SCENE_SPOT00, 7, 0x058B }, { -SCENE_SPOT00, 7, 0x058B },
    { -SCENE_SPOT00, 7, 0x858B }, { -SCENE_SPOT00, 7, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance8[] = {
    { -SCENE_SPOT00, 8, 0x0183 }, { -SCENE_SPOT00, 8, 0x0102 }, { -SCENE_SPOT00, 8, 0x8102 },
    { -SCENE_SPOT00, 8, 0x0102 }, { -SCENE_SPOT00, 8, 0x058B }, { -SCENE_SPOT00, 8, 0x058B },
    { -SCENE_SPOT00, 8, 0x058B }, { -SCENE_SPOT00, 8, 0x058B }, { -SCENE_SPOT00, 8, 0x058B },
    { -SCENE_SPOT00, 8, 0x858B }, { -SCENE_SPOT00, 8, 0x8102 },
};

static MMEntranceTableEntry sCutsceneEntrance9[] = {
    { -SCENE_SPOT00, 9, 0x0183 }, { -SCENE_SPOT00, 9, 0x0102 }, { -SCENE_SPOT00, 9, 0x8102 },
    { -SCENE_SPOT00, 9, 0x0102 }, { -SCENE_SPOT00, 9, 0x058B }, { -SCENE_SPOT00, 9, 0x058B },
    { -SCENE_SPOT00, 9, 0x058B }, { -SCENE_SPOT00, 9, 0x058B }, { -SCENE_SPOT00, 9, 0x058B },
    { -SCENE_SPOT00, 9, 0x858B }, { -SCENE_SPOT00, 9, 0x8102 },
};

static MMEntranceTableEntry* sCutsceneEntranceTable[] = {
    sCutsceneEntrance0, sCutsceneEntrance1, sCutsceneEntrance2, sCutsceneEntrance3, sCutsceneEntrance4,
    sCutsceneEntrance5, sCutsceneEntrance6, sCutsceneEntrance7, sCutsceneEntrance8, sCutsceneEntrance9,
};

#define MM_ENTRANCE(scene, spawn) ((((ENTR_SCENE_##scene) & 0x7F) << 9) | (((spawn) & 0x1F) << 4))

#define MM_SCENE_ENTRANCE(entranceTable, name) \
    { ARRAY_COUNT(entranceTable), entranceTable, name }

#define MM_SCENE_ENTRANCE_NONE() \
    { 0, NULL, NULL }

static SceneMMEntranceTableEntry sSceneEntranceTable[] = {
    /* 0x00 */ MM_SCENE_ENTRANCE(sMayorsResidenceEntranceTable, "20SICHITAI2"),
    /* 0x01 */ MM_SCENE_ENTRANCE(sMajorasLairEntranceTable, "KAKUSIANA"),
    /* 0x02 */ MM_SCENE_ENTRANCE(sMagicHagsPotionShopEntranceTable, "SPOT00"),
    /* 0x03 */ MM_SCENE_ENTRANCE(sRanchHouseEntranceTable, "WITCH_SHOP"),
    /* 0x04 */ MM_SCENE_ENTRANCE(sHoneyAndDarlingsShopEntranceTable, "LAST_BS"),
    /* 0x05 */ MM_SCENE_ENTRANCE(sBeneathTheGraveryardEntranceTable, "HAKASHITA"),
    /* 0x06 */ MM_SCENE_ENTRANCE(sSouthernSwampClearedEntranceTable, "AYASHIISHOP"),
    /* 0x07 */ MM_SCENE_ENTRANCE(sCuriosityShopEntranceTable, "OMOYA"),
    /* 0x08 */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x09 */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x0A */ MM_SCENE_ENTRANCE(sGrottosEntranceTable, "BOWLING"),
    /* 0x0B */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x0C */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x0D */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x0E */ MM_SCENE_ENTRANCE(sCutsceneEntranceTable, "SONCHONOIE"),
    /* 0x0F */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x10 */ MM_SCENE_ENTRANCE(sIkanaCanyonEntranceTable, "IKANA"),
    /* 0x11 */ MM_SCENE_ENTRANCE(sPiratesFortressEntranceTable, "KAIZOKU"),
    /* 0x12 */ MM_SCENE_ENTRANCE(sMilkBarEntranceTable, "MILK_BAR"),
    /* 0x13 */ MM_SCENE_ENTRANCE(sStoneTowerTempleEntranceTable, "INISIE_N"),
    /* 0x14 */ MM_SCENE_ENTRANCE(sTreasureChestShopEntranceTable, "TAKARAYA"),
    /* 0x15 */ MM_SCENE_ENTRANCE(sStoneTowerTempleInvertedEntranceTable, "INISIE_R"),
    /* 0x16 */ MM_SCENE_ENTRANCE(sClockTowerRooftopEntranceTable, "OKUJOU"),
    /* 0x17 */ MM_SCENE_ENTRANCE(sOpeningDungeonEntranceTable, "OPENINGDAN"),
    /* 0x18 */ MM_SCENE_ENTRANCE(sWoodfallTempleEntranceTable, "MITURIN"),
    /* 0x19 */ MM_SCENE_ENTRANCE(sPathToMountainVillageEntranceTable, "13HUBUKINOMITI"),
    /* 0x1A */ MM_SCENE_ENTRANCE(sIkanaCastleEntranceTable, "CASTLE"),
    /* 0x1B */ MM_SCENE_ENTRANCE(sDekuScrubPlaygroundEntranceTable, "DEKUTES"),
    /* 0x1C */ MM_SCENE_ENTRANCE(sOdolwasLairEntranceTable, "MITURIN_BS"),
    /* 0x1D */ MM_SCENE_ENTRANCE(sTownShootingGalleryEntranceTable, "SYATEKI_MIZU"),
    /* 0x1E */ MM_SCENE_ENTRANCE(sSnowheadTempleEntranceTable, "HAKUGIN"),
    /* 0x1F */ MM_SCENE_ENTRANCE(sMilkRoadEntranceTable, "ROMANYMAE"),
    /* 0x20 */ MM_SCENE_ENTRANCE(sPiratesFortressInteriorEntranceTable, "PIRATE"),
    /* 0x21 */ MM_SCENE_ENTRANCE(sSwampShootingGalleryEntranceTable, "SYATEKI_MORI"),
    /* 0x22 */ MM_SCENE_ENTRANCE(sPinnacleRockEntranceTable, "SINKAI"),
    /* 0x23 */ MM_SCENE_ENTRANCE(sFairyFountainEntranceTable, "YOUSEI_IZUMI"),
    /* 0x24 */ MM_SCENE_ENTRANCE(sSwampSpiderHouseEntranceTable, "KINSTA1"),
    /* 0x25 */ MM_SCENE_ENTRANCE(sOceansideSpiderHouseEntranceTable, "KINDAN2"),
    /* 0x26 */ MM_SCENE_ENTRANCE(sAstralObservatoryEntranceTable, "TENMON_DAI"),
    /* 0x27 */ MM_SCENE_ENTRANCE(sMoonDekuTrialEntranceTable, "LAST_DEKU"),
    /* 0x28 */ MM_SCENE_ENTRANCE(sDekuPalaceEntranceTable, "22DEKUCITY"),
    /* 0x29 */ MM_SCENE_ENTRANCE(sMountainSmithyEntranceTable, "KAJIYA"),
    /* 0x2A */ MM_SCENE_ENTRANCE(sTerminaFieldEntranceTable, "00KEIKOKU"),
    /* 0x2B */ MM_SCENE_ENTRANCE(sPostOfficeEntranceTable, "POSTHOUSE"),
    /* 0x2C */ MM_SCENE_ENTRANCE(sMarineResearchLabEntranceTable, "LABO"),
    /* 0x2D */ MM_SCENE_ENTRANCE(sDampesHouseEntranceTable, "DANPEI2TEST"),
    /* 0x2E */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x2F */ MM_SCENE_ENTRANCE(sGoronShrineEntranceTable, "16GORON_HOUSE"),
    /* 0x30 */ MM_SCENE_ENTRANCE(sZoraHallEntranceTable, "33ZORACITY"),
    /* 0x31 */ MM_SCENE_ENTRANCE(sTradingPostEntranceTable, "8ITEMSHOP"),
    /* 0x32 */ MM_SCENE_ENTRANCE(sRomaniRanchEntranceTable, "F01"),
    /* 0x33 */ MM_SCENE_ENTRANCE(sTwinmoldsLairEntranceTable, "INISIE_BS"),
    /* 0x34 */ MM_SCENE_ENTRANCE(sGreatBayCoastEntranceTable, "30GYOSON"),
    /* 0x35 */ MM_SCENE_ENTRANCE(sZoraCapeEntranceTable, "31MISAKI"),
    /* 0x36 */ MM_SCENE_ENTRANCE(sLotteryShopEntranceTable, "TAKARAKUJI"),
    /* 0x37 */ MM_SCENE_ENTRANCE_NONE(),
    /* 0x38 */ MM_SCENE_ENTRANCE(sPiratesFortressExteriorEntranceTable, "TORIDE"),
    /* 0x39 */ MM_SCENE_ENTRANCE(sFishermansHutEntranceTable, "FISHERMAN"),
    /* 0x3A */ MM_SCENE_ENTRANCE(sGoronShopEntranceTable, "GORONSHOP"),
    /* 0x3B */ MM_SCENE_ENTRANCE(sDekuKingsChamberEntranceTable, "DEKU_KING"),
    /* 0x3C */ MM_SCENE_ENTRANCE(sMoonGoronTrialEntranceTable, "LAST_GORON"),
    /* 0x3D */ MM_SCENE_ENTRANCE(sRoadToSouthernSwampEntranceTable, "24KEMONOMITI"),
    /* 0x3E */ MM_SCENE_ENTRANCE(sDoggyRacetrackEntranceTable, "F01_B"),
    /* 0x3F */ MM_SCENE_ENTRANCE(sCuccoShackEntranceTable, "F01C"),
    /* 0x40 */ MM_SCENE_ENTRANCE(sIkanaGraveyardEntranceTable, "BOTI"),
    /* 0x41 */ MM_SCENE_ENTRANCE(sGohtsLairEntranceTable, "HAKUGIN_BS"),
    /* 0x42 */ MM_SCENE_ENTRANCE(sSouthernSwampPoisonedEntranceTable, "20SICHITAI"),
    /* 0x43 */ MM_SCENE_ENTRANCE(sWoodfallEntranceTable, "21MITURINMAE"),
    /* 0x44 */ MM_SCENE_ENTRANCE(sMoonZoraTrialEntranceTable, "LAST_ZORA"),
    /* 0x45 */ MM_SCENE_ENTRANCE(sGoronVillageSpringEntranceTable, "11GORONNOSATO2"),
    /* 0x46 */ MM_SCENE_ENTRANCE(sGreatBayTempleEntranceTable, "SEA"),
    /* 0x47 */ MM_SCENE_ENTRANCE(sWaterfallRapidsEntranceTable, "35TAKI"),
    /* 0x48 */ MM_SCENE_ENTRANCE(sBeneathTheWellEntranceTable, "REDEAD"),
    /* 0x49 */ MM_SCENE_ENTRANCE(sZoraHallRoomsEntranceTable, "BANDROOM"),
    /* 0x4A */ MM_SCENE_ENTRANCE(sGoronVillageWinterEntranceTable, "11GORONNOSATO"),
    /* 0x4B */ MM_SCENE_ENTRANCE(sGoronGraveryardEntranceTable, "GORON_HAKA"),
    /* 0x4C */ MM_SCENE_ENTRANCE(sSakonsHideoutEntranceTable, "SECOM"),
    /* 0x4D */ MM_SCENE_ENTRANCE(sMountainVillageWinterEntranceTable, "10YUKIYAMANOMURA"),
    /* 0x4E */ MM_SCENE_ENTRANCE(sGhostHutEntranceTable, "TOUGITES"),
    /* 0x4F */ MM_SCENE_ENTRANCE(sDekuShrineEntranceTable, "DANPEI"),
    /* 0x50 */ MM_SCENE_ENTRANCE(sRoadToIkanaEntranceTable, "IKANAMAE"),
    /* 0x51 */ MM_SCENE_ENTRANCE(sSwordmansSchoolEntranceTable, "DOUJOU"),
    /* 0x52 */ MM_SCENE_ENTRANCE(sMusicBoxHouseEntranceTable, "MUSICHOUSE"),
    /* 0x53 */ MM_SCENE_ENTRANCE(sIgosDuIkanasLairEntranceTable, "IKNINSIDE"),
    /* 0x54 */ MM_SCENE_ENTRANCE(sTouristInformationEntranceTable, "MAP_SHOP"),
    /* 0x55 */ MM_SCENE_ENTRANCE(sStoneTowerEntranceTable, "F40"),
    /* 0x56 */ MM_SCENE_ENTRANCE(sStoneTowerInvertedEntranceTable, "F41"),
    /* 0x57 */ MM_SCENE_ENTRANCE(sMountainVillageSpringEntranceTable, "10YUKIYAMANOMURA2"),
    /* 0x58 */ MM_SCENE_ENTRANCE(sPathToSnowheadEntranceTable, "14YUKIDAMANOMITI"),
    /* 0x59 */ MM_SCENE_ENTRANCE(sSnowheadEntranceTable, "12HAKUGINMAE"),
    /* 0x5A */ MM_SCENE_ENTRANCE(sPathToGoronVillageWinterEntranceTable, "17SETUGEN"),
    /* 0x5B */ MM_SCENE_ENTRANCE(sPathToGoronVillageSpringEntranceTable, "17SETUGEN2"),
    /* 0x5C */ MM_SCENE_ENTRANCE(sGyorgsLairEntranceTable, "SEA_BS"),
    /* 0x5D */ MM_SCENE_ENTRANCE(sSecretShrineEntranceTable, "RANDOM"),
    /* 0x5E */ MM_SCENE_ENTRANCE(sStockPotInnEntranceTable, "YADOYA"),
    /* 0x5F */ MM_SCENE_ENTRANCE(sGreatBayCutsceneEntranceTable, "KONPEKI_ENT"),
    /* 0x60 */ MM_SCENE_ENTRANCE(sClockTowerInteriorEntranceTable, "INSIDETOWER"),
    /* 0x61 */ MM_SCENE_ENTRANCE(sWoodsOfMysteryEntranceTable, "26SARUNOMORI"),
    /* 0x62 */ MM_SCENE_ENTRANCE(sLostWoodsEntranceTable, "LOST_WOODS"),
    /* 0x63 */ MM_SCENE_ENTRANCE(sMoonLinkTrialEntranceTable, "LAST_LINK"),
    /* 0x64 */ MM_SCENE_ENTRANCE(sTheMoonEntranceTable, "SOUGEN"),
    /* 0x65 */ MM_SCENE_ENTRANCE(sBombShopEntranceTable, "BOMYA"),
    /* 0x66 */ MM_SCENE_ENTRANCE(sGiantsChamberEntranceTable, "KYOJINNOMA"),
    /* 0x67 */ MM_SCENE_ENTRANCE(sGormanTrackEntranceTable, "KOEPONARACE"),
    /* 0x68 */ MM_SCENE_ENTRANCE(sGoronRacetrackEntranceTable, "GORONRACE"),
    /* 0x69 */ MM_SCENE_ENTRANCE(sEastClockTownEntranceTable, "TOWN"),
    /* 0x6A */ MM_SCENE_ENTRANCE(sWestClockTownEntranceTable, "ICHIBA"),
    /* 0x6B */ MM_SCENE_ENTRANCE(sNorthClockTownEntranceTable, "BACKTOWN"),
    /* 0x6C */ MM_SCENE_ENTRANCE(sSouthClockTownEntranceTable, "CLOCKTOWER"),
    /* 0x6D */ MM_SCENE_ENTRANCE(sLaundryPoolEntranceTable, "ALLEY"),
};

/**
 * Returns a pointer to an entrance table from a given entrance index.
 */
MMEntranceTableEntry* MMEntrance_GetTableEntry(u16 entrance) {
    u32 entranceIndex = entrance;
    MMEntranceTableEntry** tableEntryP = sSceneEntranceTable[entranceIndex >> 9].table;
    MMEntranceTableEntry* tableEntry = tableEntryP[(entranceIndex >> 4) & 0x1F];

    return &tableEntry[entranceIndex & 0xF];
}

/**
 * Returns the scene index from a given entrance index.
 */
s32 MMEntrance_GetSceneId(u16 entrance) {
    MMEntranceTableEntry* tableEntry = MMEntrance_GetTableEntry(entrance);

    return tableEntry->sceneId;
}

/**
 * Returns the absolute value scene index (since for some reason some of them are negative) from a given entrance index.
 */
s32 MMEntrance_GetSceneIdAbsolute(u16 entrance) {
    MMEntranceTableEntry* tableEntry = MMEntrance_GetTableEntry(entrance);

    return abs(tableEntry->sceneId);
}

/**
 * Returns the spawn index from a given entrance index.
 */
s32 MMEntrance_GetSpawnNum(u16 entrance) {
    MMEntranceTableEntry* tableEntry = MMEntrance_GetTableEntry(entrance);

    return tableEntry->spawnNum;
}

/**
 * Returns the transition effect flags from a given entrance index.
 */
s32 MMEntrance_GetTransitionFlags(u16 entrance) {
    MMEntranceTableEntry* tableEntry = MMEntrance_GetTableEntry(entrance);

    return tableEntry->flags;
}

/**
 * Prints out every possible MMEntranceTableEntry
 */
void MMEntrance_PrintAll(void) {
    u32 p = 1556;
    for (u32 i = 0; i < ARRAY_COUNT(sSceneEntranceTable); i++) {
        for (u32 j = 0; j < sSceneEntranceTable[i].tableCount; j++) {
            MMEntranceTableEntry* tableEntry = &sSceneEntranceTable[i].table[j][0];
            for (u32 k = 0; k < ARRAY_COUNT(sSceneEntranceTable[i].table[j]); k++) {
                if (tableEntry->sceneId != -1) {
                    // SPDLOG_INFO("DEFINE_ENTRANCE(ENTR_{}_{}, SCENE_{}, {}, false, true, TRANS_TYPE_FADE_BLACK, TRANS_TYPE_FADE_BLACK)", sSceneEntranceTable[i].name, tableEntry->spawnNum,  sSceneEntranceTable[i].name, tableEntry->spawnNum);
                    SPDLOG_INFO("{}:{}", ((((i) & 0x7F) << 9) | (((tableEntry->spawnNum) & 0x1F) << 4)), p);
                    p++;
                }
                tableEntry++;
            }
        }
    }

}