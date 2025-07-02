#include "Minecraft.Client/resources/ResourceLocation.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/Enchantments.h"

extern MappedRegistry<ResourceLocation, Enchantment*>* sEnchantmentRegistry;

void Enchantments::staticCtor() {
    PROTECTION = Enchantments::get(L"protection");
    FIRE_PROTECTION = Enchantments::get(L"fire_protection");
    FEATHER_FALLING = Enchantments::get(L"feather_falling");
    BLAST_PROTECTION = Enchantments::get(L"blast_protection");
    PROJECTILE_PROTECTION = Enchantments::get(L"projectile_protection");
    RESPIRATION = Enchantments::get(L"respiration");
    AQUA_AFFINITY = Enchantments::get(L"aqua_affinity");
    THORNS = Enchantments::get(L"thorns");
    DEPTH_STRIDER = Enchantments::get(L"depth_strider");
    FROST_WALKER = Enchantments::get(L"frost_walker");
    BINDING_CURSE = Enchantments::get(L"binding_curse");
    SHARPNESS = Enchantments::get(L"sharpness");
    SMITE = Enchantments::get(L"smite");
    BANE_OF_ARTHROPODS = Enchantments::get(L"bane_of_arthropods");
    KNOCKBACK = Enchantments::get(L"knockback");
    FIRE_ASPECT = Enchantments::get(L"fire_aspect");
    LOOTING = Enchantments::get(L"looting");
    EFFICIENCY = Enchantments::get(L"efficiency");
    SILK_TOUCH = Enchantments::get(L"silk_touch");
    UNBREAKING = Enchantments::get(L"unbreaking");
    FORTUNE = Enchantments::get(L"fortune");
    POWER = Enchantments::get(L"power");
    PUNCH = Enchantments::get(L"punch");
    FLAME = Enchantments::get(L"flame");
    _INFINITY = Enchantments::get(L"infinity");
    LUCK_OF_THE_SEA = Enchantments::get(L"luck_of_the_sea");
    LURE = Enchantments::get(L"lure");
    MENDING = Enchantments::get(L"mending");
    VANISHING_CURSE = Enchantments::get(L"vanishing_curse");
}

Enchantment* Enchantments::get(const std::wstring& key) {
    return sEnchantmentRegistry->get(ResourceLocation(key));
}