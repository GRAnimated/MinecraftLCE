#pragma once
#include "RangedAttackMob.h"
#include "abstract/AbstractChestedHorse.h"

// ENTITY STUB
class Llama : public AbstractChestedHorse, public RangedAttackMob {
public:
    static void staticCtor();
};