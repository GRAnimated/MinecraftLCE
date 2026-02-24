#pragma once

#include <memory>

class BlockEntity;
class Textures;

class BlockEntityRenderDispatcher {
public:
    static BlockEntityRenderDispatcher* sInstance;

    static void staticCtor();

    bool hasRenderer(std::shared_ptr<BlockEntity>);

    void* m_padding[6];
    Textures* m_textures;
};
