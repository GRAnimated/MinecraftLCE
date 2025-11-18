#pragma once

#include "net/minecraft/world/entity/mob/FlyingAnimal.h"
#include "net/minecraft/world/entity/mob/ShoulderRidingEntity.h"

// ENTITY STUB
class Parrot : public ShoulderRidingEntity, public FlyingAnimal {
public:
    static void staticCtor();
};
