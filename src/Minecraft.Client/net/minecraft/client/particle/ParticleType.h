#pragma once

#include "net/minecraft/world/level/LevelListener.h"
#include <string>

class ParticleType {
public:
    ParticleType(const std::string, ePARTICLE_TYPE, bool, int);

    static void staticCtor();

    ePARTICLE_TYPE getId() const;

    std::string mName;
    ePARTICLE_TYPE mId;
    bool mUnk1;
    char idk[3];
    int mUnk2;
};
