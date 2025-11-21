#pragma once

#include "net/minecraft/world/entity/mob/abstract/AbstractChestedHorse.h"
#include "net/minecraft/world/entity/monster/RangedAttackMob.h"

// ENTITY STUB
class Llama : public AbstractChestedHorse, public RangedAttackMob {
public:
    static void staticCtor();
};
