#include "net/minecraft/world/level/block/RedSandStoneBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/SandBlock.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <string>

RedSandStoneBlock::Variant* RedSandStoneBlock::Variant::DEFAULT
    = new RedSandStoneBlock::Variant(0, L"red_sandstone", StringIDs::RedSandstone);
RedSandStoneBlock::Variant* RedSandStoneBlock::Variant::CHISELED
    = new RedSandStoneBlock::Variant(1, L"chiseled_red_sandstone", StringIDs::ChiseledRedSandstone);
RedSandStoneBlock::Variant* RedSandStoneBlock::Variant::SMOOTH
    = new RedSandStoneBlock::Variant(2, L"smooth_red_sandstone", StringIDs::SmoothRedSandstone);

RedSandStoneBlock::Variant* RedSandStoneBlock::Variant::VARIANTS[3]
    = {RedSandStoneBlock::Variant::DEFAULT, RedSandStoneBlock::Variant::CHISELED,
       RedSandStoneBlock::Variant::SMOOTH};

RedSandStoneBlock::RedSandStoneBlock() : Block(Material::STONE, SandBlock::Variant::RED->getMaterialColor()) {
    this->DerivedInit();

    const BlockState* state = this->mBlockStateDefinition->any()->setValue(TYPE, Variant::DEFAULT);
    this->registerDefaultState(state);
    memset(this->mVariantsTextures, 0, sizeof(this->mVariantsTextures));
}

void RedSandStoneBlock::blockStaticCtor() {
    RedSandStoneBlock::TYPE = EnumProperty<RedSandStoneBlock::Variant*>::create(
        L"type", typeid(RedSandStoneBlock::Variant), RedSandStoneBlock::Variant::VARIANTS,
        RedSandStoneBlock::PREDICATE);
}

const BlockState* RedSandStoneBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(TYPE, Variant::byData(data));
}

int RedSandStoneBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(TYPE)->getData();
}

int RedSandStoneBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(TYPE)->getData();
}

std::wstring RedSandStoneBlock::RED_VARIANT_TEXTURE_NAMES[3]
    = {L"red_sandstone_normal", L"red_sandstone_carved", L"red_sandstone_smooth"};
std::wstring RedSandStoneBlock::RED_SANDSTONE_TOP = L"red_sandstone_top";
std::wstring RedSandStoneBlock::RED_SANDSTONE_BOTTOM = L"red_sandstone_bottom";

void RedSandStoneBlock::registerIcons(IconRegister* iconReg) {
    this->mVariantsTextures[0] = iconReg->registerIcon(RED_VARIANT_TEXTURE_NAMES[0]);
    this->mVariantsTextures[1] = iconReg->registerIcon(RED_VARIANT_TEXTURE_NAMES[1]);
    this->mVariantsTextures[2] = iconReg->registerIcon(RED_VARIANT_TEXTURE_NAMES[2]);

    this->mTopTexture = iconReg->registerIcon(RED_SANDSTONE_TOP);
    this->mBottomTexture = iconReg->registerIcon(RED_SANDSTONE_BOTTOM);
}

TextureAtlasSprite* RedSandStoneBlock::getTexture(const Direction* direction, const BlockState* state) {
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
BlockStateDefinition* RedSandStoneBlock::createBlockStateDefinition() {
    static const Property* properties[] = {TYPE};
    return new BlockStateDefinition(this, properties);
}
