#pragma once

#include "Minecraft.World/level/block/Block.h"

class HalfTransparentBlock : public Block {
public:
    HalfTransparentBlock(const std::wstring& textureName, Material* material, bool);
    HalfTransparentBlock(const std::wstring& textureName, Material* material, bool,
                         MaterialColor const* color);

    bool shouldRenderFace(const BlockState* blockState, LevelSource* levelSource, const BlockPos& pos,
                          const Direction* direction) override;
    bool isSolidRender(const BlockState* blockState) const override;
    void registerIcons(IconRegister*) override;

private:
    bool bool_a4;
    std::wstring mTextureName;
};
