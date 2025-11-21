#pragma once

#include "net/minecraft/world/entity/mob/Monster.h"

class AbstractIllager : Monster {
public:
    static EntityDataAccessor<unsigned char>* sAccessor;

    static void staticCtor();
};
