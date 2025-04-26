#include "Minecraft.World/level/block/HalfTransparentBlock.h"

#include "Minecraft.Client/renderer/texture/IconRegister.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/material/Material.h"
#include "Minecraft.World/level/storage/LevelSource.h"
#include "Minecraft.Core/BlockPos.h"

HalfTransparentBlock::HalfTransparentBlock(const std::wstring& textureName, Material* material, bool unk)
    : Block(material, material->getColor()) {
    bool_a4 = unk;
    mTextureName = textureName;
}

HalfTransparentBlock::HalfTransparentBlock(const std::wstring& textureName, Material* material, bool unk,
                                           MaterialColor const* color)
    : Block(material, color) {
    bool_a4 = unk;
    mTextureName = textureName;
}

bool HalfTransparentBlock::shouldRenderFace(const BlockState* blockState, LevelSource* levelSource,
                                            const BlockPos& pos, const Direction* direction) {
    const BlockState* state = levelSource->getBlockState(pos.relative(direction));
    Block* relativeBlock = state->getBlock();

    if (this == Blocks::GLASS || Blocks::STAINED_GLASS == this) {
        if (blockState != state)
            return true;

        if (relativeBlock == this)
            return false;
    }

    if (!bool_a4 && relativeBlock == this)
        return false;

    return Block::shouldRenderFace(blockState, levelSource, pos, direction);
}

bool HalfTransparentBlock::isSolidRender(const BlockState* blockState) const {
    return false;
}

void HalfTransparentBlock::registerIcons(IconRegister* iconRegister) {
    mTexture = iconRegister->registerIcon(mTextureName);
}
