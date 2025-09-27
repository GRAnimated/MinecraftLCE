#pragma once

#include "Enemy.h"
#include "net/minecraft/world/entity/monster/RangedAttackMob.h"

// ENTITY STUB
class Slime : public Mob, public Enemy {
public:
    static void staticCtor();
};
