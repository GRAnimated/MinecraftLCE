#pragma once

#include "net/minecraft/world/level/block/Block.h"

class QuartzBlock : public Block {
public:
    static void blockStaticCtor();

    static std::wstring TEXTURE_NAME_TOP;           // L"top"
    static std::wstring TEXTURE_NAME_CHISELED_TOP;  // L"chiseled_top"
    static std::wstring TEXTURE_NAME_LINES_TOP;     // L"lines_top"
    static std::wstring TEXTURE_NAME_BOTTOM;        // L"bottom"
    static std::wstring TEXTURE_NAMES[5];

    QuartzBlock();
    ~QuartzBlock() override;

    RenderShape getRenderShape(const BlockState* blockState) override;
    int getSpawnResourcesAuxValue(const BlockState* blockState) override;
    const BlockState* getStateForPlacement(Level* level, const BlockPos& pos, const Direction* direction,
                                           float, float, float, int, std::shared_ptr<LivingEntity>) override;
    void getSilkTouchItemInstance(const BlockState* blockState) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction* direction, const BlockState* blockState) override;
    BlockStateDefinition* createBlockStateDefinition() override;

private:
    TextureAtlasSprite* mTextures[5];
    TextureAtlasSprite* mTextureChiseledTop;
    TextureAtlasSprite* mTextureLinesTop;
    TextureAtlasSprite* mTextureTop;
    TextureAtlasSprite* mTextureBottom;
};
