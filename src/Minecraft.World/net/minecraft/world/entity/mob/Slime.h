#pragma once
#include "Enemy.h"
#include "Mob.h"

// ENTITY STUB
class Slime : public Mob, public Enemy {
public:
    static void staticCtor();
};