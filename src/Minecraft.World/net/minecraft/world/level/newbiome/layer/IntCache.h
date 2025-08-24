#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class IntCache {
public:
    static arrayWithLength<int> allocate(int size);

    static void CreateNewThreadStorage();

    static void releaseAll();

    static void ReleaseThreadStorage();

    static void Reset();

    class ThreadStorage {};
};
