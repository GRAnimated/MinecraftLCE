#pragma once

#include "FlyingMob.h"
#include "net/minecraft/world/entity/mob/Enemy.h"

// ENTITY STUB
class Ghast : public FlyingMob, public Enemy {
public:
    static void staticCtor();
};
