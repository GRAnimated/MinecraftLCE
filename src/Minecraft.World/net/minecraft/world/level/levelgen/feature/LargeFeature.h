#pragma once

class ChunkPrimer;
class Level;

class LargeFeature {
public:
    virtual ~LargeFeature();
    virtual void apply(Level*, int, int, ChunkPrimer*);
    virtual void addFeature(Level*, int, int, int, int, ChunkPrimer*);
};
