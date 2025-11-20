#pragma once

#include "net/minecraft/world/entity/mob/abstract/AbstractHorse.h"

class AbstractChestedHorse : public AbstractHorse {
public:
    static EntityDataAccessor<bool>* sAccessor;

    static void staticCtor();
};
