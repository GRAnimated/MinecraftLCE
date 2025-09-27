#pragma once

#include "net/minecraft/world/entity/mob/Creature.h"
#include "net/minecraft/world/entity/mob/Mob.h"

// ENTITY STUB
class AmbientCreature : public Mob, public Creature {
public:
    static void staticCtor();
};
