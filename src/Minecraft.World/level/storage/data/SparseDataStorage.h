#pragma once
#include "Minecraft.Core/io/DataOutputStream.h"

class SparseDataStorage {
public:
    void write(DataOutputStream* out);
    void tick();
    static void staticCtor();
};
