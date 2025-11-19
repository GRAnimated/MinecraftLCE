#pragma once

#include "net/minecraft/world/level/LevelListener.h"
#include <string>

class ParticleType {
public:
    ParticleType(const std::string, ePARTICLE_TYPE, bool, int);

    ePARTICLE_TYPE getId() const;

    std::string mName;
    ePARTICLE_TYPE mId;
    bool mUnk1;
    char idk[3];
    int mUnk2;

    static ParticleType EXPLODE;
    static ParticleType SPIT;
    static ParticleType BUBBLE;
    static ParticleType SPLASH;
    static ParticleType WAKE;
    static ParticleType DROPLET;
    static ParticleType SUSPENDED;
    static ParticleType DEPTHSUSPEND;
    static ParticleType CRIT;
    static ParticleType MAGIC_CRIT;
    static ParticleType SMOKE;
    static ParticleType LARGE_SMOKE;
    static ParticleType SPELL;
    static ParticleType INSTANT_SPELL;
};
