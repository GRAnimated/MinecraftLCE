#pragma once
#include "GenericStats.h"

// STUB
class CommonStats : public GenericStats {
public:
    static CommonStats *sInstance;

    static void setInstance(CommonStats *instance) {
        sInstance = instance;
    }

    Stat* get_stat(int) override;
};