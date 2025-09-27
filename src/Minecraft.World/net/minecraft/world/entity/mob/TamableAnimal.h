#pragma once

#include "net/minecraft/world/entity/OwnableEntity.h"
#include "net/minecraft/world/entity/mob/FlyingAnimal.h"

// ENTITY STUB
class TamableAnimal : public Animal, public OwnableEntity {
public:
    static void staticCtor();
};
