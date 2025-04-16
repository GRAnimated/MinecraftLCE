#pragma once

class Textures;

class BlockEntityRenderDispatcher {
    public:
    static BlockEntityRenderDispatcher *sInstance;

    void* padding[6];
    Textures *mTextures;
};