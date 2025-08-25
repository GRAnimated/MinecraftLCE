#pragma once

class ChunkPrimer;

class GenericOverworldLevelSource {
public:
    GenericOverworldLevelSource() {}

    virtual void prepareHeights(int, int, ChunkPrimer*);
    // missing a second unknown virtual function
};
