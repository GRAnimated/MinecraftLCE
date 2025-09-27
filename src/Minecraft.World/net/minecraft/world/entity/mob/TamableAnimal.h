#pragma once
#include "Animal.h"
#include "net/minecraft/world/entity/OwnableEntity.h"

// ENTITY STUB
class TamableAnimal : public Animal, public OwnableEntity {
public:
    static void staticCtor();
};