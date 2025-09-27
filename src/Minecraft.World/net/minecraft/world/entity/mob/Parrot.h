#pragma once
#include "FlyingAnimal.h"
#include "ShoulderRidingEntity.h"

// ENTITY STUB
class Parrot : public ShoulderRidingEntity, public FlyingAnimal {
public:
    static void staticCtor();
};