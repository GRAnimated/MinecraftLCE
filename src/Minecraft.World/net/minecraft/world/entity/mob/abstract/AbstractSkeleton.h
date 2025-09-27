#pragma once

#include "net/minecraft/world/entity/mob/Monster.h"
#include "net/minecraft/world/entity/mob/RangedAttackMob.h"

class AbstractSkeleton : public Monster, public RangedAttackMob {
public:
    static EntityDataAccessor<bool>* sAccessor;

    static void staticCtor();
};
