#pragma once

#include "Golem.h"
#include "net/minecraft/world/entity/monster/RangedAttackMob.h"

// ENTITY STUB
class SnowMan : public Golem, public RangedAttackMob {
public:
    static void staticCtor();
};
