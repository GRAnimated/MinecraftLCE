#pragma once

#include "net/minecraft/world/level/LevelListener.h"
#include <string>

class ParticleType {
public:
    ParticleType(const std::string, ePARTICLE_TYPE, bool, int);

    static void staticCtor();

    ePARTICLE_TYPE getId() const;

    std::string m_name;
    ePARTICLE_TYPE m_id;
    bool m_unk1;
    char m_idk[3];
    int m_unk2;
};
