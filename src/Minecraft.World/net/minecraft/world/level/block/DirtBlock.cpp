#include "DirtBlock.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/item/InteractionResultHolder.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/BlockTooltipDataHolder.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include "net/minecraft/world/level/storage/LevelSource.h"

static DirtBlock::Variant* DIRT;
static DirtBlock::Variant* COARSE;
static DirtBlock::Variant* PODZOL;

static DirtBlock::Variant* VARIANTS[3];

DirtBlock::DirtBlock() : Block(Material::DIRT) {
    this->DerivedInit();
    this->registerDefaultState(
        this->m_blockStateDefinition->any()->setValue(VARIANT, Variant::DIRT)->setValue(SNOWY, false));
}

void DirtBlock::blockStaticCtor() {
    Variant::DIRT = new Variant(0, L"dirt", StringIDs::Dirt, StringIDs::CollectedUsingAShovelCanBeUsedFor,
                                MaterialColor::DIRT, L"dirt", L"", L"");
    Variant::COARSE = new Variant(1, L"coarse_dirt", StringIDs::CoarseDirt,
                                  StringIDs::ASpecialTypeOfDirtThatDoesNotGrowGrass, MaterialColor::DIRT,
                                  L"coarse_dirt", L"", L"");
    Variant::PODZOL
        = new Variant(2, L"podzol", StringIDs::Podzol, StringIDs::SimilarToDirtBlocksButVeryGoodFor,
                      MaterialColor::PODZOL, L"dirt", L"dirt_podzol_top", L"dirt_podzol_side");

    Variant::VARIANTS[0] = Variant::DIRT;
    Variant::VARIANTS[1] = Variant::COARSE;
    Variant::VARIANTS[2] = Variant::PODZOL;

    VARIANT = EnumProperty<Variant*>::create(L"variant", typeid(Variant), Variant::VARIANTS, PREDICATE);
}

int DirtBlock::GetInteractTooltip(const BlockTooltipDataHolder& dataHolder) {
    if (dataHolder.m_itemInstance->getItem()->getId() - 290 > 4
        || dataHolder.m_interactionResult != InteractionResult::SUCCESS || !dataHolder.m_belowBuildHeight
        || dataHolder.m_blockState->getValue<Variant*>(VARIANT) == Variant::PODZOL) {
        return Block::GetInteractTooltip(dataHolder);
    } else {
        return StringIDs::Till;
    }
}

const MaterialColor* DirtBlock::getMapColor(const BlockState* state, LevelSource*, const BlockPos&) {
    return state->getValue<Variant*>(VARIANT)->getMaterialColor();
}

// NON_MATCHING: static code gen to be fixed
const BlockState* DirtBlock::getBlockState(int data) {
    static const BlockState* states[3] = {this->defaultBlockState()->setValue(VARIANT, Variant::byData(0)),
                                          this->defaultBlockState()->setValue(VARIANT, Variant::byData(1)),
                                          this->defaultBlockState()->setValue(VARIANT, Variant::byData(2))};

    return states[data > 2 ? 0 : data];
}

int DirtBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

const BlockState* DirtBlock::fillVirtualBlockStateProperties(const BlockState* state, LevelSource* level,
                                                             const BlockPos& pos) {
    const BlockState* ret = state;
    if (state->getValue<Variant*>(VARIANT) == Variant::PODZOL) {
        const BlockState* stateAbove = level->getBlockState(pos.above());
        Block* blockAbove = stateAbove->getBlock();

        ret = ret->setValue(SNOWY, blockAbove == Blocks::SNOW || blockAbove == Blocks::SNOW_LAYER);
    }
    return ret;
}

int DirtBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    Variant* variant = state->getValue<Variant*>(VARIANT);
    if (variant == Variant::PODZOL) {
        variant = Variant::DIRT;
    }
    return variant->getData();
}

not_null_ptr<ItemInstance> DirtBlock::getCloneItemInstance(Level*, const BlockPos&, const BlockState* state) {
    return new ItemInstance(this, 1, state->getValue<Variant*>(VARIANT)->getData());
}

void DirtBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < 3; i++)
        Variant::VARIANTS[i]->registerIcons(iconReg);
}

TextureAtlasSprite* DirtBlock::getTexture(const Direction* dir, const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getTexture(dir);
}

// NON_MATCHING: static code gen to be fixed
BlockStateDefinition* DirtBlock::createBlockStateDefinition() {
    static const Property* properties[2]{VARIANT, SNOWY};
    return new BlockStateDefinition(this, properties);
}
