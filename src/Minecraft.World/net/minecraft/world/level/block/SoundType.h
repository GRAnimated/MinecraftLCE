#pragma once

class SoundEvent;

class SoundType {
public:
    static const SoundType* STONE;
    static const SoundType* WOOD;
    static const SoundType* GRASS;
    static const SoundType* DIRT;
    static const SoundType* SAND;
    static const SoundType* METAL;
    static const SoundType* GLASS;
    static const SoundType* WOOL;
    static const SoundType* LADDER;
    static const SoundType* SNOW;
    static const SoundType* SLIME_BLOCK;
    static const SoundType* ANVIL;

    static void staticCtor();

    SoundType(float volume, float pitch, const SoundEvent* dig, const SoundEvent* step,
              const SoundEvent* place, const SoundEvent* hit, const SoundEvent* fall);

    float m_volume;
    float m_pitch;
    SoundEvent* m_digSound;
    SoundEvent* m_stepSound;
    SoundEvent* m_placeSound;
    SoundEvent* m_hitSound;
    SoundEvent* m_fallSound;
};
