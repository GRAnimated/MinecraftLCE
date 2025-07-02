#include "net/minecraft/world/level/block/HalfTransparentBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/storage/LevelSource.h"

HalfTransparentBlock::HalfTransparentBlock(const std::wstring& textureName, Material* material, bool unk)
    : Block(material, material->getColor()) {
    bool_a4 = unk;
    mTextureName = textureName;
}

HalfTransparentBlock::HalfTransparentBlock(const std::wstring& textureName, Material* material, bool unk,
                                           const MaterialColor* color)
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
