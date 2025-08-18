#include "net/minecraft/world/level/block/SandStoneBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <cstring>
#include <string>

SandStoneBlock::Variant* SandStoneBlock::Variant::DEFAULT
    = new SandStoneBlock::Variant(0, L"sandstone", StringIDs::Sandstone);
SandStoneBlock::Variant* SandStoneBlock::Variant::CHISELED
    = new SandStoneBlock::Variant(1, L"chiseled_sandstone", StringIDs::ChiseledSandstone);
SandStoneBlock::Variant* SandStoneBlock::Variant::SMOOTH
    = new SandStoneBlock::Variant(2, L"smooth_sandstone", StringIDs::SmoothSandstone);

SandStoneBlock::Variant* SandStoneBlock::Variant::VARIANTS[3]
    = {SandStoneBlock::Variant::DEFAULT, SandStoneBlock::Variant::CHISELED, SandStoneBlock::Variant::SMOOTH};

SandStoneBlock::SandStoneBlock() : Block(Material::STONE) {
    this->DerivedInit();

    const BlockState* state = this->mBlockStateDefinition->any()->setValue(TYPE, Variant::DEFAULT);
    this->registerDefaultState(state);
    memset(this->mVariantsTextures, 0, sizeof(this->mVariantsTextures));
}

void SandStoneBlock::blockStaticCtor() {
    SandStoneBlock::TYPE = EnumProperty<SandStoneBlock::Variant*>::create(
        L"type", typeid(SandStoneBlock::Variant), SandStoneBlock::Variant::VARIANTS,
        SandStoneBlock::PREDICATE);
}

MaterialColor* SandStoneBlock::getMapColor(const BlockState*, LevelSource*, const BlockPos&) {
    return MaterialColor::SAND;
}

const BlockState* SandStoneBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(TYPE, Variant::byData(data));
}

int SandStoneBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(TYPE)->getData();
}

int SandStoneBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(TYPE)->getData();
}

std::wstring SandStoneBlock::VARIANT_TEXTURE_NAMES[3]
    = {L"sandstone_side", L"sandstone_carved", L"sandstone_smooth"};
std::wstring SandStoneBlock::SANDSTONE_TOP = L"sandstone_top";
std::wstring SandStoneBlock::SANDSTONE_BOTTOM = L"sandstone_bottom";

void SandStoneBlock::registerIcons(IconRegister* iconReg) {
    this->mVariantsTextures[0] = iconReg->registerIcon(VARIANT_TEXTURE_NAMES[0]);
    this->mVariantsTextures[1] = iconReg->registerIcon(VARIANT_TEXTURE_NAMES[1]);
    this->mVariantsTextures[2] = iconReg->registerIcon(VARIANT_TEXTURE_NAMES[2]);

    this->mTopTexture = iconReg->registerIcon(SANDSTONE_TOP);
    this->mBottomTexture = iconReg->registerIcon(SANDSTONE_BOTTOM);
}

TextureAtlasSprite* SandStoneBlock::getTexture(const Direction* direction, const BlockState* state) {
    Variant* variant = state->getValue<Variant*>(TYPE);
    if (direction == Direction::UP)
        return this->mTopTexture;
    if (direction != Direction::DOWN)
        return this->mVariantsTextures[variant->getData()];
    if (variant != Variant::CHISELED && variant != Variant::SMOOTH)
        return this->mBottomTexture;

    return this->mTopTexture;
}

// NON_MATCHING: see comment below
BlockStateDefinition* SandStoneBlock::createBlockStateDefinition() {
    static const Property* properties[1]{TYPE};  // this is not generating the same way as target is
    BlockStateDefinition* ret = new BlockStateDefinition(this, properties);
    return ret;
}
