#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/StoneBlock.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <cstring>

StoneBlock::StoneBlock() : Block(Material::STONE) {
    Block::DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::STONE));
}

void StoneBlock::blockStaticCtor() {
    Variant::STONE = new Variant(0, MaterialColor::STONE, L"stone", 0x8BAD4DAC, 0x46782239, L"stone", true);
    Variant::GRANITE
        = new Variant(1, MaterialColor::DIRT, L"granite", 0x19244F91, 0x91114554, L"stone_granite", true);
    Variant::SMOOTH_GRANITE = new Variant(2, MaterialColor::DIRT, L"smooth_granite", 0x567CEDEE, 0x25E3FDC3,
                                          L"stone_smooth_granite", false);
    Variant::DIORITE
        = new Variant(3, MaterialColor::QUARTZ, L"diorite", 0x77F221B3, 0x5E93DB6, L"stone_diorite", true);
    Variant::SMOOTH_DIORITE = new Variant(4, MaterialColor::QUARTZ, L"smooth_diorite", 0xF1C0B35C, 0x2A4CCCF1,
                                          L"stone_diorite_smooth", false);
    Variant::ANDESITE
        = new Variant(5, MaterialColor::STONE, L"andesite", 0xBD013DC6, 0xF2A753FB, L"stone_andesite", true);
    Variant::SMOOTH_ANDESITE = new Variant(6, MaterialColor::STONE, L"smooth_andesite", 0x1BB05261,
                                           0x47BE1614, L"stone_andesite_smooth", false);

    Variant::VARIANTS[0] = Variant::STONE;
    Variant::VARIANTS[1] = Variant::GRANITE;
    Variant::VARIANTS[2] = Variant::SMOOTH_GRANITE;
    Variant::VARIANTS[3] = Variant::DIORITE;
    Variant::VARIANTS[4] = Variant::SMOOTH_DIORITE;
    Variant::VARIANTS[5] = Variant::ANDESITE;
    Variant::VARIANTS[6] = Variant::SMOOTH_ANDESITE;

    VARIANT = EnumProperty<StoneBlock::Variant*>::create(
        L"variant", typeid(StoneBlock::Variant), StoneBlock::Variant::VARIANTS,
        (Predicates<StoneBlock::Variant*>*)StoneBlock::PREDICATE);
}

const MaterialColor* StoneBlock::getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                             const BlockPos& pos) {
    return blockState->getValue<Variant*>(VARIANT)->getMaterialColor();
}

const BlockState* StoneBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int StoneBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int StoneBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

void StoneBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < 7; i++)  // idk if 4J used for loop but I find this, way cleaner
        Variant::VARIANTS[i]->registerIcons(iconReg);
}

TextureAtlasSprite* StoneBlock::getTexture(const Direction*, const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getTexture();
}

// NON_MATCHING: static initalizer is different than target
BlockStateDefinition* StoneBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}

std::wstring StoneBlock::getName() {
    return L10N::GetString(0x8BAD4DAC);
}

Item* StoneBlock::getResource(const BlockState* state, Random*, int) {
    return Item::byBlock(state->getValue<Variant*>(VARIANT) == Variant::STONE ? Blocks::COBBLESTONE :
                                                                                Blocks::STONE);
}