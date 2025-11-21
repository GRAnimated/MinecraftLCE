#pragma once

#include "java/io/DataOutputStream.h"

class SparseLightStorage {
public:
    void write(DataOutputStream* out);

    static void staticCtor();
};
