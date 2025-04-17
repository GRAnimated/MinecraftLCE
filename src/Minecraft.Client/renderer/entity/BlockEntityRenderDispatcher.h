#pragma once

class Textures;

class BlockEntityRenderDispatcher {
public:
    static BlockEntityRenderDispatcher* sInstance;

    static void staticCtor();

    void* padding[6];
    Textures* mTextures;
};