#pragma once
#include "java/io/DataOutputStream.h"

class SparseDataStorage {
public:
    void write(DataOutputStream* out);
    void tick();
    static void staticCtor();
};
