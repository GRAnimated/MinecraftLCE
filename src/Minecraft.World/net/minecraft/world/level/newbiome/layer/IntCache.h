#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include <vector>

class IntCache {
public:
    static arrayWithLength<int> allocate(int size);

    static void CreateNewThreadStorage();

    static void releaseAll();

    static void ReleaseThreadStorage();

    static void Reset();

    class ThreadStorage {
    public:
        ThreadStorage();
        ~ThreadStorage();

        // Arrays remain owned here; returned arrayWithLength values are views.
        int m_maxSize;
        std::vector<arrayWithLength<int>> m_freeSmall;
        std::vector<arrayWithLength<int>> m_activeSmall;
        std::vector<arrayWithLength<int>> m_freeLarge;
        std::vector<arrayWithLength<int>> m_activeLarge;
        std::vector<arrayWithLength<int>> m_retiredLarge;
    };

    static unsigned int sThreadStorageIndex;
};
