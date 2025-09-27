#pragma once
#include "Creature.h"
#include "Mob.h"

// ENTITY STUB
class AmbientCreature : public Mob, public Creature {
public:
    static void staticCtor();
};