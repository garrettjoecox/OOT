#ifndef ROGUELIKE_CHOICES_HPP
#define ROGUELIKE_CHOICES_HPP

#include "soh/Enhancements/randomizer/3drando/random.hpp"
#include <string>
#include <functional>

extern "C" {
#include "variables.h"
#include "macros.h"
#include "functions.h"

extern PlayState* gPlayState;
}

namespace RogueLike {

namespace Choices {

typedef struct ChoiceCard {
    std::string textureName;
    std::string name;
    uint32_t value;
    std::function<bool(uint32_t value)> canSelect;
    std::function<void(uint32_t value)> onSelect;
} ChoiceCard;

inline bool CanAlwaysSelect(uint32_t value) {
    return true;
}

inline void OnSelectLocation(uint32_t value) {
    gSaveContext.cutsceneIndex = 0;
    gSaveContext.entranceIndex = value;
}

inline void Noop(uint32_t value) {
}

#define LOCATION_CHOICE(texture, name, entrance) \
    { #texture, name, entrance, CanAlwaysSelect, OnSelectLocation }

inline std::vector<ChoiceCard> Locations = {
    LOCATION_CHOICE(ITEM_KOKIRI_EMERALD, "Kokiri Forest", ENTR_LINKS_HOUSE_CHILD_SPAWN),
    LOCATION_CHOICE(ITEM_GORON_RUBY, "Goron City", ENTR_GORON_CITY_UPPER_EXIT),
    LOCATION_CHOICE(ITEM_SCALE_SILVER, "Lake Hylia", ENTR_LAKE_HYLIA_WARP_PAD),
    LOCATION_CHOICE(ITEM_ZORA_SAPPHIRE, "Zora's Domain", ENTR_ZORAS_DOMAIN_ENTRANCE),
    LOCATION_CHOICE(ITEM_MEDALLION_SPIRIT, "Desert Colossus", ENTR_DESERT_COLOSSUS_WARP_PAD),
    LOCATION_CHOICE(ITEM_SKULL_TOKEN, "Ganon's Castle", ENTR_GANONS_TOWER_0)
};

inline bool CanSelectSong(uint32_t value) {
    return !CHECK_QUEST_ITEM(value - ITEM_SONG_MINUET + QUEST_SONG_MINUET);
}

inline void GiveItem(uint32_t value) {
    Item_Give(gPlayState, value);
}

inline bool IsItemInSlot(uint32_t value) {
    return gSaveContext.inventory.items[SLOT(value)] == ITEM_NONE;
}

inline void UpgradeMagic(uint32_t value) {
    if (value == ITEM_MAGIC_SMALL) {
        gSaveContext.isMagicAcquired = true;
        gSaveContext.magicFillTarget = MAGIC_NORMAL_METER;
        Magic_Fill(gPlayState);
    } else if (value == ITEM_MAGIC_LARGE) {
        if (!gSaveContext.isMagicAcquired) {
            gSaveContext.isMagicAcquired = true;
        }
        gSaveContext.isDoubleMagicAcquired = true;
        gSaveContext.magicFillTarget = MAGIC_DOUBLE_METER;
        gSaveContext.magicLevel = 0;
        Magic_Fill(gPlayState);
    }
}

#define SONG_CHOICE(song, name) \
    { "QUEST_SONG_" #song, name, ITEM_SONG_##song, CanSelectSong, GiveItem }

inline std::vector<ChoiceCard> Songs = {
    SONG_CHOICE(MINUET, "Minuet of Forest"),     SONG_CHOICE(BOLERO, "Bolero of Fire"),
    SONG_CHOICE(SERENADE, "Serenade of Water"),  SONG_CHOICE(REQUIEM, "Requiem of Spirit"),
    SONG_CHOICE(NOCTURNE, "Nocturne of Shadow"), SONG_CHOICE(PRELUDE, "Prelude of Light"),
    SONG_CHOICE(LULLABY, "Zelda's Lullaby"),     SONG_CHOICE(EPONA, "Epona's Song"),
    SONG_CHOICE(SARIA, "Saria's Song"),          SONG_CHOICE(SUN, "Sun's Song"),
    SONG_CHOICE(TIME, "Song of Time"),           SONG_CHOICE(STORMS, "Song of Storms"),
};

#define ITEM_CHOICE(item, name) \
    { #item, name, item, IsItemInSlot, GiveItem }

inline std::vector<ChoiceCard> Items = {
    ITEM_CHOICE(ITEM_STICK, "Deku Stick"),
    ITEM_CHOICE(ITEM_NUT, "Deku Nut"),
    ITEM_CHOICE(ITEM_BOW, "Bow"),
    ITEM_CHOICE(ITEM_SLINGSHOT, "Slingshot"),
    ITEM_CHOICE(ITEM_BOTTLE, "Bottle"),
    { "ITEM_BOMB", "Bombs", ITEM_BOMB_BAG_20,
      [](int32_t _) { return gSaveContext.inventory.items[SLOT(ITEM_BOMB)] == ITEM_NONE; }, GiveItem },
    { "ITEM_BOMBCHU", "Bombchu", ITEM_BOMBCHUS_20,
      [](int32_t _) {
          return gSaveContext.inventory.items[SLOT(ITEM_BOMB)] != ITEM_NONE && IsItemInSlot(ITEM_BOMBCHU);
      },
      GiveItem },
    ITEM_CHOICE(ITEM_HOOKSHOT, "Hookshot"),
    // Longshot requires hookshot
    { "ITEM_LONGSHOT", "Longshot", ITEM_LONGSHOT,
      [](int32_t _) { return gSaveContext.inventory.items[SLOT(ITEM_LONGSHOT)] == ITEM_HOOKSHOT; }, GiveItem },
    ITEM_CHOICE(ITEM_MASK_BUNNY, "Bunny Hood"),
    ITEM_CHOICE(ITEM_OCARINA_FAIRY, "Fairy Ocarina"),
    ITEM_CHOICE(ITEM_ARROW_FIRE, "Fire Arrow"),
    ITEM_CHOICE(ITEM_ARROW_ICE, "Ice Arrow"),
    ITEM_CHOICE(ITEM_ARROW_LIGHT, "Light Arrow"),
    ITEM_CHOICE(ITEM_BOOMERANG, "Boomerang"),
    ITEM_CHOICE(ITEM_HAMMER, "Megaton Hammer"),
    ITEM_CHOICE(ITEM_LENS, "Lens of Truth"),
    ITEM_CHOICE(ITEM_DINS_FIRE, "Din's Fire"),
    ITEM_CHOICE(ITEM_FARORES_WIND, "Farore's Wind"),
    ITEM_CHOICE(ITEM_NAYRUS_LOVE, "Nayru's Love"),
};

inline bool IsRLStatUnder100(uint32_t value) {
    return gSaveContext.ship.quest.data.rogueLike.stats[value] < 100;
}

inline void IncreaseRLStat(uint32_t value) {
    gSaveContext.ship.quest.data.rogueLike.stats[value]++;
}

#define STAT_CHOICE(texture, stat, name) \
    { #texture, name, stat, IsRLStatUnder100, IncreaseRLStat }

inline std::vector<ChoiceCard> Stats = {
    STAT_CHOICE(ITEM_SWORD_KOKIRI, RL_ATTACK, "Attack"),
    STAT_CHOICE(ITEM_SHIELD_DEKU, RL_DEFENSE, "Defense"),
    STAT_CHOICE(ITEM_MASK_BUNNY, RL_SPEED, "Speed"),
};

#define EQUIP_CHOICE(item, name, equipType, equipInv)                                                  \
    {                                                                                                  \
#item, name, item, [](int32_t _) { return !CHECK_OWNED_EQUIP(equipType, equipInv); }, GiveItem \
    }

inline std::vector<ChoiceCard> Equipment = {
    EQUIP_CHOICE(ITEM_SWORD_KOKIRI, "Kokiri Sword", EQUIP_TYPE_SWORD, EQUIP_INV_SWORD_KOKIRI),
    EQUIP_CHOICE(ITEM_SWORD_MASTER, "Master Sword", EQUIP_TYPE_SWORD, EQUIP_INV_SWORD_MASTER),
    EQUIP_CHOICE(ITEM_SHIELD_DEKU, "Deku Shield", EQUIP_TYPE_SHIELD, EQUIP_INV_SHIELD_DEKU),
    EQUIP_CHOICE(ITEM_SHIELD_HYLIAN, "Hylian Shield", EQUIP_TYPE_SHIELD, EQUIP_INV_SHIELD_HYLIAN),
    EQUIP_CHOICE(ITEM_SHIELD_MIRROR, "Mirror Shield", EQUIP_TYPE_SHIELD, EQUIP_INV_SHIELD_MIRROR),
    EQUIP_CHOICE(ITEM_TUNIC_GORON, "Goron Tunic", EQUIP_TYPE_TUNIC, EQUIP_INV_TUNIC_GORON),
    EQUIP_CHOICE(ITEM_TUNIC_ZORA, "Zora Tunic", EQUIP_TYPE_TUNIC, EQUIP_INV_TUNIC_ZORA),
    EQUIP_CHOICE(ITEM_BOOTS_IRON, "Iron Boots", EQUIP_TYPE_BOOTS, EQUIP_INV_BOOTS_IRON),
    EQUIP_CHOICE(ITEM_BOOTS_HOVER, "Hover Boots", EQUIP_TYPE_BOOTS, EQUIP_INV_BOOTS_HOVER),
    { "ITEM_SCALE_SILVER", "Silver Scale", ITEM_SCALE_SILVER, [](int32_t _) { return CUR_UPG_VALUE(UPG_SCALE) == 0; },
      GiveItem },
    { "ITEM_SCALE_GOLDEN", "Golden Scale", ITEM_SCALE_GOLDEN, [](int32_t _) { return CUR_UPG_VALUE(UPG_SCALE) == 1; },
      GiveItem },
    { "ITEM_BRACELET", "Goron Bracelet", ITEM_BRACELET, [](int32_t _) { return CUR_UPG_VALUE(UPG_STRENGTH) == 0; },
      GiveItem },
    { "ITEM_GAUNTLETS_SILVER", "Silver Gauntlets", ITEM_GAUNTLETS_SILVER,
      [](int32_t _) { return CUR_UPG_VALUE(UPG_STRENGTH) == 1; }, GiveItem },
    { "ITEM_GAUNTLETS_GOLD", "Golden Gauntlets", ITEM_GAUNTLETS_GOLD,
      [](int32_t _) { return CUR_UPG_VALUE(UPG_STRENGTH) == 2; }, GiveItem },
    { "ITEM_MAGIC_SMALL", "Magic", ITEM_MAGIC_SMALL, [](int32_t _) { return !gSaveContext.isMagicAcquired; },
      UpgradeMagic },
    { "ITEM_MAGIC_LARGE", "Large Magic", ITEM_MAGIC_LARGE,
      [](int32_t _) { return gSaveContext.isMagicAcquired && !gSaveContext.isDoubleMagicAcquired; }, UpgradeMagic },
};

inline std::vector<ChoiceCard> All = {
    { "ITEM_SWORD_KOKIRI", "Stat Increase", 0,
      [](uint32_t _) {
          for (auto& statChoice : Stats) {
              if (statChoice.canSelect(statChoice.value)) {
                  return true;
              }
          }
          return false;
      },
      Noop },
    { "ITEM_BOW", "Item", 1,
      [](uint32_t _) {
          for (auto& itemChoice : Items) {
              if (itemChoice.canSelect(itemChoice.value)) {
                  return true;
              }
          }
          return false;
      },
      Noop },
    { "ITEM_SHIELD_DEKU", "Equipment", 2,
      [](uint32_t _) {
          for (auto& equipmentChoice : Equipment) {
              if (equipmentChoice.canSelect(equipmentChoice.value)) {
                  return true;
              }
          }
          return false;
      },
      Noop },
    { "ITEM_SONG_MINUET", "Song", 3,
      [](uint32_t _) {
          for (auto& songChoice : Songs) {
              if (songChoice.canSelect(songChoice.value)) {
                  return true;
              }
          }
          return false;
      },
      Noop },
};

inline std::vector<ChoiceCard*> Choose3Max(std::vector<ChoiceCard>& allChoices) {
    std::vector<ChoiceCard*> choices = {};

    for (auto& choice : allChoices) {
        if (choice.canSelect(choice.value)) {
            choices.push_back(&choice);
        }
    }

    Shuffle(choices);

    if (choices.size() > 3) {
        choices.resize(3);
    }

    return choices;
}

} // namespace Choices

} // namespace RogueLike

#endif // ROGUELIKE_CHOICES_HPP
