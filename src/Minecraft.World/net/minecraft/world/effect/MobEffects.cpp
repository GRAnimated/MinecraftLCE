#include "net/minecraft/world/effect/MobEffects.h"

#include "net/minecraft/world/effect/MobEffect.h"

MobEffect* MobEffects::SPEED;
MobEffect* MobEffects::SLOWNESS;
MobEffect* MobEffects::HASTE;
MobEffect* MobEffects::MINING_FATIGUE;
MobEffect* MobEffects::STRENGTH;
MobEffect* MobEffects::INSTANT_HEALTH;
MobEffect* MobEffects::INSTANT_DAMAGE;
MobEffect* MobEffects::JUMP_BOOST;
MobEffect* MobEffects::NAUSEA;
MobEffect* MobEffects::REGENERATION;
MobEffect* MobEffects::RESISTANCE;
MobEffect* MobEffects::FIRE_RESISTANCE;
MobEffect* MobEffects::WATER_BREATHING;
MobEffect* MobEffects::INVISIBILITY;
MobEffect* MobEffects::BLINDNESS;
MobEffect* MobEffects::NIGHT_VISION;
MobEffect* MobEffects::HUNGER;
MobEffect* MobEffects::WEAKNESS;
MobEffect* MobEffects::POISON;
MobEffect* MobEffects::WITHER;
MobEffect* MobEffects::HEALTH_BOOST;
MobEffect* MobEffects::ABSORPTION;
MobEffect* MobEffects::SATURATION;
MobEffect* MobEffects::GLOWING;
MobEffect* MobEffects::LEVITATION;
MobEffect* MobEffects::LUCK;
MobEffect* MobEffects::UNLUCK;

MobEffect* MobEffects::get(const std::wstring& name) {
    return MobEffect::REGISTRY->get(ResourceLocation(name));
}

void MobEffects::staticCtor() {
    SPEED = get(L"speed");
    SLOWNESS = get(L"slowness");
    HASTE = get(L"haste");
    MINING_FATIGUE = get(L"mining_fatigue");
    STRENGTH = get(L"strength");
    INSTANT_HEALTH = get(L"instant_health");
    INSTANT_DAMAGE = get(L"instant_damage");
    JUMP_BOOST = get(L"jump_boost");
    NAUSEA = get(L"nausea");
    REGENERATION = get(L"regeneration");
    RESISTANCE = get(L"resistance");
    FIRE_RESISTANCE = get(L"fire_resistance");
    WATER_BREATHING = get(L"water_breathing");
    INVISIBILITY = get(L"invisibility");
    BLINDNESS = get(L"blindness");
    NIGHT_VISION = get(L"night_vision");
    HUNGER = get(L"hunger");
    WEAKNESS = get(L"weakness");
    POISON = get(L"poison");
    WITHER = get(L"wither");
    HEALTH_BOOST = get(L"health_boost");
    ABSORPTION = get(L"absorption");
    SATURATION = get(L"saturation");
    GLOWING = get(L"glowing");
    LEVITATION = get(L"levitation");
    LUCK = get(L"luck");
    UNLUCK = get(L"unluck");
}
