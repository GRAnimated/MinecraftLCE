#pragma once

#include "BossMob.h"
#include "RangedAttackMob.h"
#include "net/minecraft/world/entity/mob/Monster.h"

// ENTITY STUB
class WitherBoss : public Monster, public RangedAttackMob, public BossMob {
public:
    static void staticCtor();
};