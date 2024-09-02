#include "Block.h"

#include "Minecraft.World/level/block/state/BlockState.h"
#include "Minecraft.World/level/block/state/BlockStateDefinition.h"
#include "Minecraft.World/level/block/SoundType.h"
#include "Minecraft.World/level/material/Material.h"

Block::Block(Material* material) {
    init(material, material->getColor());
}

Block::Block(Material* material, const MaterialColor* color) {
    init(material, color);
}

const BlockState* Block::defaultBlockState() {
    return mBlockState;
}

void Block::registerDefaultState(const BlockState* blockState) {
    mBlockState = blockState;
}

void Block::init(Material* material, const MaterialColor* color) {
    field_A0 = 0;
    mExplosionResistance = 0.0f;
    mIsCollectStatistics = true;

    mSoundType = SoundType::STONE;

    mDestroyTime = 0.0f;
    mIsTicking = false;
    mIsSilkTouchable = false;
    field_60 = 1.0f;
    mFriction = 0.6f;
    mMaterial = material;
    mMapColor = color;
    mLightEmission = 0;

    bool isEnableLight = material->blocksLight();

    isDisableMipmap = true;
    isSemiTransparent = false;
    field_3C = false;
    mMaterialType = 0;
    mBaseItemType = 0;

    isBlocksLight = !isEnableLight;

    mTexture = nullptr;
    isInited = false;
    field_8 = 0;
    field_C = false;
}

void Block::DerivedInit() {
    isInited = true;

    mBlockStateDefinition = createBlockStateDefinition();
    registerDefaultState(mBlockStateDefinition->any());

    bool isSolidRender = defaultBlockState()->isSolidRender();
    field_28 = isSolidRender;
    lightEmission = isSolidRender ? 255 : 0;
}
