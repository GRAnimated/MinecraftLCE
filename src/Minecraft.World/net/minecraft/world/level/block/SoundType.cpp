#include "net/minecraft/world/level/block/SoundType.h"

#include "net/minecraft/sounds/SoundEvent.h"
#include "net/minecraft/sounds/SoundEvents.h"

const SoundType* SoundType::WOOD;
const SoundType* SoundType::DIRT;  // name guessed
const SoundType* SoundType::GRASS;
const SoundType* SoundType::STONE;
const SoundType* SoundType::METAL;  // name guessed
const SoundType* SoundType::GLASS;
const SoundType* SoundType::WOOL;
const SoundType* SoundType::SAND;  // name guessed
const SoundType* SoundType::SNOW;
const SoundType* SoundType::LADDER;
const SoundType* SoundType::ANVIL;  // name guessed
const SoundType* SoundType::SLIME_BLOCK;

SoundType::SoundType(float volume, float pitch, const SoundEvent* dig, const SoundEvent* step,
                     const SoundEvent* place, const SoundEvent* hit, const SoundEvent* fall)
    : m_volume(volume), m_pitch(pitch), m_digSound(dig), m_stepSound(step), m_placeSound(place),
      m_hitSound(hit), m_fallSound(fall) {}

// name guessed
const SoundEvent* SoundType::getBreakSound() {
    return m_digSound;
}
// name guessed
const SoundEvent* SoundType::getStepSound() {
    return m_stepSound;
}
// name guessed
const SoundEvent* SoundType::getHitSound() {
    return m_hitSound;
}
// name guessed
const SoundEvent* SoundType::getFallSound() {
    return m_fallSound;
}

// name guessed
void SoundType::staticCtor() {
    WOOD = new SoundType(1.0f, 1.0f, SoundEvents::DIG_WOOD_4, SoundEvents::STEP_WOOD_3,
                         SoundEvents::DIG_WOOD_5, SoundEvents::STEP_WOOD_2, SoundEvents::STEP_WOOD);
    DIRT = new SoundType(1.0f, 1.0f, SoundEvents::DIG_GRAVEL, SoundEvents::STEP_GRAVEL_3,
                         SoundEvents::DIG_GRAVEL_2, SoundEvents::STEP_GRAVEL_2, SoundEvents::STEP_GRAVEL);
    GRASS = new SoundType(1.0f, 1.0f, SoundEvents::DIG_GRASS, SoundEvents::STEP_GRASS_3,
                          SoundEvents::DIG_GRASS_2, SoundEvents::STEP_GRASS_2, SoundEvents::STEP_GRASS);
    STONE = new SoundType(1.0f, 1.0f, SoundEvents::DIG_STONE_6, SoundEvents::STEP_STONE_11,
                          SoundEvents::DIG_STONE_7, SoundEvents::STEP_STONE_10, SoundEvents::STEP_STONE_9);
    METAL = new SoundType(1.0f, 1.5f, SoundEvents::DIG_STONE_4, SoundEvents::STEP_STONE_8,
                          SoundEvents::DIG_STONE_5, SoundEvents::STEP_STONE_7, SoundEvents::STEP_STONE_6);
    GLASS = new SoundType(1.0f, 1.0f, SoundEvents::RANDOM_GLASS, SoundEvents::STEP_STONE_5,
                          SoundEvents::DIG_STONE_3, SoundEvents::STEP_STONE_4, SoundEvents::STEP_STONE_3);
    WOOL = new SoundType(1.0f, 1.0f, SoundEvents::DIG_CLOTH, SoundEvents::STEP_CLOTH_3,
                         SoundEvents::DIG_CLOTH_2, SoundEvents::STEP_CLOTH_2, SoundEvents::STEP_CLOTH);
    SAND = new SoundType(1.0f, 1.0f, SoundEvents::DIG_SAND, SoundEvents::STEP_SAND_3, SoundEvents::DIG_SAND_2,
                         SoundEvents::STEP_SAND_2, SoundEvents::STEP_SAND);
    SNOW = new SoundType(1.0f, 1.0f, SoundEvents::DIG_SNOW, SoundEvents::STEP_SNOW_3, SoundEvents::DIG_SNOW_2,
                         SoundEvents::STEP_SNOW_2, SoundEvents::STEP_SNOW);
    LADDER = new SoundType(1.0f, 1.0f, SoundEvents::DIG_WOOD_2, SoundEvents::STEP_LADDER_3,
                           SoundEvents::DIG_WOOD_3, SoundEvents::STEP_LADDER_2, SoundEvents::STEP_LADDER);
    ANVIL = new SoundType(0.30000001f, 1.0f, SoundEvents::DIG_STONE, SoundEvents::STEP_STONE_2,
                          SoundEvents::RANDOM_ANVIL_LAND_3, SoundEvents::STEP_STONE,
                          SoundEvents::RANDOM_ANVIL_LAND);
    SLIME_BLOCK = new SoundType(1.0f, 1.0f, SoundEvents::MOB_SLIME_BIG_3, SoundEvents::MOB_SLIME_SMALL_3,
                                SoundEvents::MOB_SLIME_BIG_4, SoundEvents::MOB_SLIME_SMALL_2,
                                SoundEvents::MOB_SLIME_SMALL);
}
