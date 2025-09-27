#pragma once

#include "net/minecraft/world/entity/mob/RangedAttackMob.h"
#include "net/minecraft/world/entity/mob/Monster.h"

// ENTITY STUB
class Witch : public Monster, public RangedAttackMob {
public:
    static void staticCtor();
};
