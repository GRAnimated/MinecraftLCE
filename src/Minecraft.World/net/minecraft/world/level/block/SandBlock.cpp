#include "net/minecraft/world/level/block/SandBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <cstring>

SandBlock::SandBlock() : FallingBlock() {
    Block::DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::DEFAULT));
    memset(this->mVariantsTextures, 0, sizeof(this->mVariantsTextures));
}

void SandBlock::blockStaticCtor() {
    Variant::DEFAULT
        = new Variant(0, L"sand", StringIDs::Sand, StringIDs::CollectedUsingAShovelCanBeSmeltedInto,
                      MaterialColor::SAND, 0xFFDBD3A0);
    Variant::RED = new Variant(1, L"red_sand", StringIDs::RedSand, StringIDs::ARedColoredSandThatCanBeFound,
                               MaterialColor::COLOR_ORANGE, 0xFFA95821);
    Variant::VARIANTS[0] = Variant::DEFAULT;
    Variant::VARIANTS[1] = Variant::RED;

    VARIANT = EnumProperty<SandBlock::Variant*>::create(L"type", typeid(SandBlock::Variant),
                                                        SandBlock::Variant::VARIANTS, SandBlock::PREDICATE);
}

const MaterialColor* SandBlock::getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                            const BlockPos& pos) {
    return blockState->getValue<Variant*>(VARIANT)->getMaterialColor();
}

const BlockState* SandBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int SandBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int SandBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

void SandBlock::registerIcons(IconRegister* iconReg) {
    this->mVariantsTextures[0] = iconReg->registerIcon(Variant::VARIANTS[0]->getName());
    this->mVariantsTextures[1] = iconReg->registerIcon(Variant::VARIANTS[1]->getName());
}

TextureAtlasSprite* SandBlock::getTexture(const Direction*, const BlockState* state) {
    return this->mVariantsTextures[state->getValue<Variant*>(VARIANT)->getData()];
}

// NON_MATCHING: static initalizer is different than target
BlockStateDefinition* SandBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}

int SandBlock::getDustColor(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getDustColor();
}
