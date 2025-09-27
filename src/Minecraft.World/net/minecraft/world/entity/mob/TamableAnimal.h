#pragma once

#include "net/minecraft/world/entity/mob/FlyingAnimal.h"
#include "net/minecraft/world/entity/OwnableEntity.h"

// ENTITY STUB
class TamableAnimal : public Animal, public OwnableEntity {
public:
    static void staticCtor();
};
