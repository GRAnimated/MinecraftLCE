#pragma once

class ChunkPrimer;

class GenericOverworldLevelSource {
public:
    virtual void prepareHeights(int, int, ChunkPrimer*) = 0;
    virtual bool isFlat();
};
