#include "net/minecraft/world/level/block/PlanksBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
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

std::wstring PlanksBlock::variantTextureNames[6]
    = {L"oak", L"spruce", L"birch", L"jungle", L"acacia", L"big_oak"};

PlanksBlock::PlanksBlock() : Block(Material::WOOD) {
    this->DerivedInit();

    const BlockState* state = this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::OAK);
    this->registerDefaultState(state);
    memset(this->mVariantsTextures, 0, sizeof(this->mVariantsTextures));
}

void PlanksBlock::blockStaticCtor() {
    Variant::OAK = new Variant(0, L"oak", 0x13035FA5, MaterialColor::WOOD);
    Variant::SPRUCE = new Variant(1, L"spruce", 0x7A4DF272, MaterialColor::PODZOL);
    Variant::BIRCH = new Variant(2, L"birch", 0x9BC6104A, MaterialColor::SAND);
    Variant::JUNGLE = new Variant(3, L"jungle", 0x8CE369FC, MaterialColor::DIRT);
    Variant::ACACIA = new Variant(4, L"acacia", 0x674A2380, MaterialColor::COLOR_ORANGE);
    Variant::DARK_OAK = new Variant(5, L"dark_oak", 0x458BC59, MaterialColor::COLOR_BROWN);

    PlanksBlock::Variant::VARIANTS[0] = PlanksBlock::Variant::OAK;
    PlanksBlock::Variant::VARIANTS[1] = PlanksBlock::Variant::SPRUCE;
    PlanksBlock::Variant::VARIANTS[2] = PlanksBlock::Variant::BIRCH;
    PlanksBlock::Variant::VARIANTS[3] = PlanksBlock::Variant::JUNGLE;
    PlanksBlock::Variant::VARIANTS[4] = PlanksBlock::Variant::ACACIA;
    PlanksBlock::Variant::VARIANTS[5] = PlanksBlock::Variant::DARK_OAK;

    PlanksBlock::VARIANT = EnumProperty<PlanksBlock::Variant*>::create(
        L"variant", typeid(PlanksBlock::Variant), PlanksBlock::Variant::VARIANTS, PlanksBlock::PREDICATE);
}

const MaterialColor* PlanksBlock::getMapColor(const BlockState* state, LevelSource*, const BlockPos&) {
    return state->getValue<Variant*>(VARIANT)->getMaterialColor();
}

const BlockState* PlanksBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int PlanksBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int PlanksBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

void PlanksBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < 6; i++) {
        this->mVariantsTextures[i]
            = iconReg->registerIcon(this->getIconName() + L"_" + variantTextureNames[i]);
    }
}

TextureAtlasSprite* PlanksBlock::getTexture(const Direction* direction, const BlockState* state) {
    return this->mVariantsTextures[state->getValue<Variant*>(VARIANT)->getData()];
}

unsigned int planks_block_desc_ids[6] = {0x13035FA5, 0x7A4DF272, 0x9BC6104A, 0x8CE369FC, 0x674A2380};
unsigned int PlanksBlock::getDescriptionId(int data) {
    return planks_block_desc_ids[data > (sizeof(planks_block_desc_ids) / sizeof(int)) - 1 ?
                                     0 :
                                     data];  // it became hard to match those lol
}

// NON_MATCHING: see comment below
BlockStateDefinition* PlanksBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};  // this is not generating the same way as target is
    BlockStateDefinition* ret = new BlockStateDefinition(this, properties);
    return ret;
}
