#pragma once

#include "net/minecraft/world/entity/mob/BossMob.h"
#include "net/minecraft/world/entity/mob/Monster.h"
#include "net/minecraft/world/entity/monster/RangedAttackMob.h"

// ENTITY STUB
class WitherBoss : public Monster, public RangedAttackMob, public BossMob {
public:
    static void staticCtor();
};
