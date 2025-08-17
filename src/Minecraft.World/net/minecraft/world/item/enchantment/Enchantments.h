#pragma once

#include <string>

class Enchantment;

class Enchantments {
public:
    static Enchantment* PROTECTION;
    static Enchantment* FIRE_PROTECTION;
    static Enchantment* FEATHER_FALLING;
    static Enchantment* BLAST_PROTECTION;
    static Enchantment* PROJECTILE_PROTECTION;
    static Enchantment* RESPIRATION;
    static Enchantment* AQUA_AFFINITY;
    static Enchantment* THORNS;
    static Enchantment* DEPTH_STRIDER;
    static Enchantment* FROST_WALKER;
    static Enchantment* BINDING_CURSE;
    static Enchantment* SHARPNESS;
    static Enchantment* SMITE;
    static Enchantment* BANE_OF_ARTHROPODS;
    static Enchantment* KNOCKBACK;
    static Enchantment* FIRE_ASPECT;
    static Enchantment* LOOTING;
    static Enchantment* EFFICIENCY;
    static Enchantment* SILK_TOUCH;
    static Enchantment* UNBREAKING;
    static Enchantment* FORTUNE;
    static Enchantment* POWER;
    static Enchantment* PUNCH;
    static Enchantment* FLAME;
    static Enchantment* _INFINITY;  // this name cause it cries beacuse INFINITY is already part of math
    static Enchantment* LUCK_OF_THE_SEA;
    static Enchantment* LURE;
    static Enchantment* MENDING;
    static Enchantment* VANISHING_CURSE;

    static void staticCtor();
    static Enchantment* get(const std::wstring&);
};
