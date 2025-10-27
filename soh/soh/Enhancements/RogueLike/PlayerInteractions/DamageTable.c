#include "DamageTable.h"

DamageTable rogueLikeEnemyDamageTable = {
    /* Deku nut      */ DMG_ENTRY(0, DMGEFF_DEKU_NUT),
    /* Deku stick    */ DMG_ENTRY(0, DMGEFF_DEKU_STICK),
    /* Slingshot     */ DMG_ENTRY(0, DMGEFF_SLINGSHOT),
    /* Explosive     */ DMG_ENTRY(0, DMGEFF_EXPLOSIVE),
    /* Boomerang     */ DMG_ENTRY(0, DMGEFF_BOOMERANG),
    /* Normal arrow  */ DMG_ENTRY(0, DMGEFF_ARROW),
    /* Hammer swing  */ DMG_ENTRY(0, DMGEFF_HAMMER_SWING),
    /* Hookshot      */ DMG_ENTRY(0, DMGEFF_HOOKSHOT),
    /* Kokiri sword  */ DMG_ENTRY(0, DMGEFF_SWORD_KOKIRI),
    /* Master sword  */ DMG_ENTRY(0, DMGEFF_SWORD_MASTER),
    /* Giant's Knife */ DMG_ENTRY(0, DMGEFF_SWORD_KNIFE),
    /* Fire arrow    */ DMG_ENTRY(0, DMGEFF_ARROW_FIRE),
    /* Ice arrow     */ DMG_ENTRY(0, DMGEFF_ARROW_ICE),
    /* Light arrow   */ DMG_ENTRY(0, DMGEFF_ARROW_LIGHT),
    /* Unk arrow 1   */ DMG_ENTRY(0, DMGEFF_ARROW_UNKNOWN_1),
    /* Unk arrow 2   */ DMG_ENTRY(0, DMGEFF_ARROW_UNKNOWN_2),
    /* Unk arrow 3   */ DMG_ENTRY(0, DMGEFF_ARROW_UNKNOWN_3),
    /* Fire magic    */ DMG_ENTRY(0, DMGEFF_MAGIC_FIRE),
    /* Ice magic     */ DMG_ENTRY(0, DMGEFF_MAGIC_ICE),
    /* Light magic   */ DMG_ENTRY(0, DMGEFF_MAGIC_LIGHT),
    /* Shield        */ DMG_ENTRY(0, DMGEFF_SHIELD),
    /* Mirror Ray    */ DMG_ENTRY(0, DMGEFF_MIRROR_RAY),
    /* Kokiri spin   */ DMG_ENTRY(0, DMGEFF_SWORD_SPIN_KOKIRI),
    /* Giant spin    */ DMG_ENTRY(0, DMGEFF_SWORD_SPIN_KNIFE),
    /* Master spin   */ DMG_ENTRY(0, DMGEFF_SWORD_SPIN_MASTER),
    /* Kokiri jump   */ DMG_ENTRY(0, DMGEFF_SWORD_JUMP_KOKIRI),
    /* Giant jump    */ DMG_ENTRY(0, DMGEFF_SWORD_JUMP_KNIFE),
    /* Master jump   */ DMG_ENTRY(0, DMGEFF_SWORD_JUMP_MASTER),
    /* Unknown 1     */ DMG_ENTRY(0, DMGEFF_UNKNOWWN_1),
    /* Unblockable   */ DMG_ENTRY(0, DMGEFF_UNBLOCKABLE),
    /* Hammer jump   */ DMG_ENTRY(0, DMGEFF_HAMMER_JUMP),
    /* Unknown 2     */ DMG_ENTRY(0, DMGEFF_UNKNOWN_2),
};

DamageTable GetModifiedDamageTable(Actor* refActor) {
    DamageTable baseDamageTable = rogueLikeEnemyDamageTable;
    switch (refActor->id) {
        case ACTOR_EN_DEKUBABA: /* Deku Baba */
            baseDamageTable.table[DMGEFF_DEKU_STICK] = DMG_ENTRY(2, DMGEFF_DEKU_STICK);
        case ACTOR_EN_AM: /* Armos */ 
        case ACTOR_EN_ANUBICE: /* Anubis */
        case ACTOR_EN_BB: /* Floating Skulls */
            if (refActor->params == -1) {} // Blue & Green
            if (refActor->params == -2) {} // Red
            if (refActor->params == -3) {} // White
        case ACTOR_EN_BILI: /* Biri Jellyfish */
        case ACTOR_EN_BW: /* Torch Slug */
        case ACTOR_EN_CROW: /* Guay */
        case ACTOR_EN_DODONGO: /* Dodongo */
        case ACTOR_EN_EIYER: /* ?? */
        case ACTOR_EN_FIREFLY: /* Keese */
        case ACTOR_EN_FLOORMAS: /* Floormaster */
        default:
            break;
    }
    return baseDamageTable;
};