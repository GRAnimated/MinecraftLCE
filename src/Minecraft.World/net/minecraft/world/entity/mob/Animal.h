#pragma once

#include "net/minecraft/world/entity/mob/AgableMob.h"
#include "net/minecraft/network/syncher/EntityDataAccessor.h"
#include "net/minecraft/world/entity/mob/Creature.h"

class Animal : public AgableMob, public Creature {
public:
    static EntityDataAccessor<int>* sAccessor;

    static void staticCtor();
};
