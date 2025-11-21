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

    SoundType(float volume, float pitch, const SoundEvent* dig, const SoundEvent* step,
              const SoundEvent* place, const SoundEvent* hit, const SoundEvent* fall);

    float mVolume;
    float mPitch;
    SoundEvent* mDigSound;
    SoundEvent* mStepSound;
    SoundEvent* mPlaceSound;
    SoundEvent* mHitSound;
    SoundEvent* mFallSound;
};
