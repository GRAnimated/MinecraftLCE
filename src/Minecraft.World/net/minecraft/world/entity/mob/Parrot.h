#pragma once

#include "ShoulderRidingEntity.h"
#include "net/minecraft/world/entity/mob/FlyingAnimal.h"

// ENTITY STUB
class Parrot : public ShoulderRidingEntity, public FlyingAnimal {
public:
    static void staticCtor();
};
