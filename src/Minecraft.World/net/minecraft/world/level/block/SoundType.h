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

    const SoundEvent* getBreakSound();
    const SoundEvent* getStepSound();
    const SoundEvent* getHitSound();
    const SoundEvent* getFallSound();

    float m_volume;
    float m_pitch;
    const SoundEvent* m_digSound;
    const SoundEvent* m_stepSound;
    const SoundEvent* m_placeSound;
    const SoundEvent* m_hitSound;
    const SoundEvent* m_fallSound;
};
