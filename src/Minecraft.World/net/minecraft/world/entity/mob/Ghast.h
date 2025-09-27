#pragma once
#include "Enemy.h"
#include "FlyingMob.h"

// ENTITY STUB
class Ghast : public FlyingMob, public Enemy {
public:
    static void staticCtor();
};