#include "net/minecraft/world/level/block/StoneBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <cstring>

StoneBlock::StoneBlock() : Block(Material::STONE) {
    Block::DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::STONE));
}

void StoneBlock::blockStaticCtor() {
    Variant::STONE = new Variant(0, MaterialColor::STONE, L"stone", StringIDs::Stone,
                                 StringIDs::CanBeMinedWithAPickaxeToCollectCobblestone, L"stone", true);
    Variant::GRANITE = new Variant(1, MaterialColor::DIRT, L"granite", StringIDs::Granite,
                                   StringIDs::CanBeMinedWithAPickaxeToCollectGranite, L"stone_granite", true);
    Variant::SMOOTH_GRANITE
        = new Variant(2, MaterialColor::DIRT, L"smooth_granite", StringIDs::PolishedGranite,
                      StringIDs::CanBeCraftedFromGraniteForAPolishedLook, L"stone_smooth_granite", false);
    Variant::DIORITE = new Variant(3, MaterialColor::QUARTZ, L"diorite", StringIDs::Diorite, 0x5E93DB6,
                                   L"stone_diorite", true);
    Variant::SMOOTH_DIORITE
        = new Variant(4, MaterialColor::QUARTZ, L"smooth_diorite", StringIDs::PolishedDiorite,
                      StringIDs::CanBeCraftedFromDioriteForAPolishedLook, L"stone_diorite_smooth", false);
    Variant::ANDESITE
        = new Variant(5, MaterialColor::STONE, L"andesite", StringIDs::Andesite,
                      StringIDs::CanBeMinedWithAPickaxeToCollectAndesite, L"stone_andesite", true);
    Variant::SMOOTH_ANDESITE
        = new Variant(6, MaterialColor::STONE, L"smooth_andesite", StringIDs::PolishedAndesite,
                      StringIDs::CanBeCraftedFromAndesiteForAPolishedLook, L"stone_andesite_smooth", false);

    Variant::VARIANTS[0] = Variant::STONE;
    Variant::VARIANTS[1] = Variant::GRANITE;
    Variant::VARIANTS[2] = Variant::SMOOTH_GRANITE;
    Variant::VARIANTS[3] = Variant::DIORITE;
    Variant::VARIANTS[4] = Variant::SMOOTH_DIORITE;
    Variant::VARIANTS[5] = Variant::ANDESITE;
    Variant::VARIANTS[6] = Variant::SMOOTH_ANDESITE;

    VARIANT = EnumProperty<StoneBlock::Variant*>::create(
        L"variant", typeid(StoneBlock::Variant), StoneBlock::Variant::VARIANTS, StoneBlock::PREDICATE);
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
    return L10N::GetString(StringIDs::Stone);
}

Item* StoneBlock::getResource(const BlockState* state, Random*, int) {
    return Item::byBlock(state->getValue<Variant*>(VARIANT) == Variant::STONE ? Blocks::COBBLESTONE :
                                                                                Blocks::STONE);
}
