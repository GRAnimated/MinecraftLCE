#pragma once

#include "AbstractHorse.h"

class AbstractChestedHorse : public AbstractHorse {
public:
    static EntityDataAccessor<bool>* sAccessor;

    static void staticCtor();
};
