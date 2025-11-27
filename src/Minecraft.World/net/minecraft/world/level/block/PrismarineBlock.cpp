#include "net/minecraft/world/level/block/PrismarineBlock.h"

#include "net/minecraft/client/ui/StringIDs.h"

#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

PrismarineBlock::Variant* PrismarineBlock::Variant::ROUGH
    = new PrismarineBlock::Variant(0, L"prismarine", StringIDs::Prismarine,
                                   StringIDs::RareDecorativeStoneThatCanBeFoundIn, L"prismarine_rough");
PrismarineBlock::Variant* PrismarineBlock::Variant::BRICKS = new PrismarineBlock::Variant(
    1, L"prismarine_bricks", StringIDs::PrismarineBricks,
    StringIDs::DecorativePrismarineBrickThatCanBeFoundIn, L"prismarine_bricks");
PrismarineBlock::Variant* PrismarineBlock::Variant::DARK
    = new PrismarineBlock::Variant(2, L"dark_prismarine", StringIDs::DarkPrismarine,
                                   StringIDs::ARarerFormOfPrismarineThatCanBe, L"prismarine_dark");

int PrismarineBlock::ROUGH_DATA = -1;
int PrismarineBlock::BRICKS_DATA = -1;
int PrismarineBlock::DARK_DATA = -1;

PrismarineBlock::Variant* PrismarineBlock::Variant::VARIANTS[3]{
    PrismarineBlock::Variant::ROUGH, PrismarineBlock::Variant::BRICKS, PrismarineBlock::Variant::DARK};

PrismarineBlock::PrismarineBlock() : Block(Material::STONE) {
    this->DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::ROUGH));
}

void PrismarineBlock::blockStaticCtor() {
    VARIANT = EnumProperty<Variant*>::create(L"variant", typeid(Variant), Variant::VARIANTS, PREDICATE);

    ROUGH_DATA = Variant::ROUGH->getData();
    BRICKS_DATA = Variant::BRICKS->getData();
    DARK_DATA = Variant::DARK->getData();
}

const MaterialColor* PrismarineBlock::getMapColor(const BlockState* state, LevelSource*, const BlockPos&) {
    return state->getValue<Variant*>(VARIANT) == Variant::ROUGH ? MaterialColor::COLOR_CYAN :
                                                                  MaterialColor::DIAMOND;
}

const BlockState* PrismarineBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int PrismarineBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int PrismarineBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

std::wstring PrismarineBlock::getName() {
    return L10N::GetString(StringIDs::Prismarine);
}

void PrismarineBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < (sizeof(Variant::VARIANTS) / sizeof(Variant*)); i++)
        Variant::VARIANTS[i]->registerIcons(iconReg);
}

TextureAtlasSprite* PrismarineBlock::getTexture(const Direction*, const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getTexture();
}

// NON_MATCHING: static array handling is generated differently
BlockStateDefinition* PrismarineBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}
