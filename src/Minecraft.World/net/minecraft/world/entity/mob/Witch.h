#pragma once

#include "net/minecraft/world/entity/mob/Monster.h"
#include "net/minecraft/world/entity/monster/RangedAttackMob.h"

// ENTITY STUB
class Witch : public Monster, public RangedAttackMob {
public:
    static void staticCtor();
};
