#pragma once

#include "net/minecraft/world/Random.h"

class ChunkPrimer;
class Level;

class LargeFeature {
public:
    virtual ~LargeFeature();
    virtual void apply(Level*, int, int, ChunkPrimer*);
    virtual void addFeature(Level*, int, int, int, int, ChunkPrimer*);

    int m_radius;
    Random m_random;
    void* m_unused;
};
