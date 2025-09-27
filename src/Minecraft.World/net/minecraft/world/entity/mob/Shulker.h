#pragma once
#include "Enemy.h"
#include "Golem.h"

// ENTITY STUB
// why the fuck is this a golem
class Shulker : public Golem, public Enemy{
public:
    static void staticCtor();
};