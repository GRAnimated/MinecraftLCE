#pragma once

#include <memory>

class BlockEntity;
class Textures;

class BlockEntityRenderDispatcher {
public:
    static BlockEntityRenderDispatcher* sInstance;

    static void staticCtor();

    bool hasRenderer(std::shared_ptr<BlockEntity>);

    void* padding[6];
    Textures* mTextures;
};