#pragma once

#include "nn/os/os_MutexTypes.h"
#include "types.h"
class Level;
class Minecraft;
class Textures;

class LevelRenderer {
public:
    static LevelRenderer* sInstance;

    LevelRenderer(Minecraft* mc, Textures* textures);

    static int getGlobalIndexForChunk(int, int, int, Level*);
    unsigned char incGlobalChunkRefCount(int, int, int, Level*);
    unsigned char decGlobalChunkRefCount(int, int, int, Level*);
    void setGlobalChunkFlag(int, int, int, Level*, unsigned char, unsigned char);
    void setGlobalChunkFlags(int, int, int, Level*, unsigned char);
    void clearGlobalChunkFlag(int, int, int, Level*, unsigned char, unsigned char);

    void* filler[32];
    int _100;
    void* filler2[61];
    nn::os::MutexType mMutex;
    void* filler3[13];
};

ASSERT_SIZEOF(LevelRenderer, 0x378)
