#pragma once

#include "net/minecraft/world/entity/mob/Enemy.h"
#include "FlyingMob.h"

// ENTITY STUB
class Ghast : public FlyingMob, public Enemy {
public:
    static void staticCtor();
};
