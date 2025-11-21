#pragma once

#include "net/minecraft/world/entity/mob/Enemy.h"
#include "net/minecraft/world/entity/mob/Golem.h"

// ENTITY STUB
// why the fuck is this a golem
class Shulker : public Golem, public Enemy {
public:
    static void staticCtor();
};
