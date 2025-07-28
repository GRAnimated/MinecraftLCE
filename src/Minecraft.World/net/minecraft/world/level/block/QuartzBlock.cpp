#include "net/minecraft/world/level/block/QuartzBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/BlockShapes.h"
#include "net/minecraft/world/level/block/Rotation.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/material/Material.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include "types.h"
#include <string>

QuartzBlock::Variant* QuartzBlock::Variant::DEFAULT = new QuartzBlock::Variant(0, L"default", L"default");
QuartzBlock::Variant* QuartzBlock::Variant::CHISELED = new QuartzBlock::Variant(1, L"chiseled", L"chiseled");
QuartzBlock::Variant* QuartzBlock::Variant::LINES_Y = new QuartzBlock::Variant(2, L"lines_y", L"lines_y");
QuartzBlock::Variant* QuartzBlock::Variant::LINES_X = new QuartzBlock::Variant(3, L"lines_x", L"lines_x");
QuartzBlock::Variant* QuartzBlock::Variant::LINES_Z = new QuartzBlock::Variant(4, L"lines_z", L"lines_z");

QuartzBlock::Variant* QuartzBlock::Variant::VARIANTS[5]{
    QuartzBlock::Variant::DEFAULT, QuartzBlock::Variant::CHISELED, QuartzBlock::Variant::LINES_Y,
    QuartzBlock::Variant::LINES_X, QuartzBlock::Variant::LINES_Z};

QuartzBlock::QuartzBlock() : Block(Material::STONE) {
    Block::DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::DEFAULT));
}

void QuartzBlock::blockStaticCtor() {
    VARIANT = EnumProperty<QuartzBlock::Variant*>::create(
        L"variant", typeid(QuartzBlock::Variant), QuartzBlock::Variant::VARIANTS,
        (Predicates<QuartzBlock::Variant*>*)QuartzBlock::PREDICATE);
}

const MaterialColor* QuartzBlock::getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                              const BlockPos& pos) {
    return MaterialColor::QUARTZ;
}

const BlockState* QuartzBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

const BlockState* QuartzBlock::rotate(const BlockState* state, Rotation* rotate) {
    switch (rotate->getType()) {
    case Rotation::ROTATE_270:
    case Rotation::ROTATE_90:
        switch (state->getValue<Variant*>(VARIANT)->getData()) {
        case 3:
            return state->setValue(VARIANT, Variant::LINES_Z);
        case 4:
            return state->setValue(VARIANT, Variant::LINES_X);
        default:
            return state;
        }
    default:
        return state;
    }
}

RenderShape QuartzBlock::getRenderShape(const BlockState* blockState) {
    return RenderShape_QUARTZ;
}

int QuartzBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int QuartzBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    Variant* variant = state->getValue<Variant*>(VARIANT);
    if (variant == Variant::LINES_X || variant == Variant::LINES_Z)
        variant = Variant::LINES_Y;

    return variant->getData();
}

std::wstring QuartzBlock::TEXTURE_NAME_TOP = L"top";
std::wstring QuartzBlock::TEXTURE_NAME_CHISELED_TOP = L"chiseled_top";
std::wstring QuartzBlock::TEXTURE_NAME_LINES_TOP = L"lines_top";
std::wstring QuartzBlock::TEXTURE_NAME_BOTTOM = L"bottom";
std::wstring QuartzBlock::TEXTURE_NAMES[5] = {L"side", L"chiseled", L"lines", L"", L""};

void QuartzBlock::registerIcons(IconRegister* iconRegister) {
    for (int i = 0; i < 5; i++) {
        if (!TEXTURE_NAMES[i].empty()) {
            mTextures[i] = iconRegister->registerIcon(getIconName() + L"_" + TEXTURE_NAMES[i]);
        } else {
            mTextures[i] = mTextures[i - 1];
        }
    }

    mTextureTop = iconRegister->registerIcon(getIconName() + L"_" + TEXTURE_NAME_TOP);
    mTextureChiseledTop = iconRegister->registerIcon(getIconName() + L"_" + TEXTURE_NAME_CHISELED_TOP);
    mTextureLinesTop = iconRegister->registerIcon(getIconName() + L"_" + TEXTURE_NAME_LINES_TOP);
    mTextureBottom = iconRegister->registerIcon(getIconName() + L"_" + TEXTURE_NAME_BOTTOM);
}

// TODO: do this
// TextureAtlasSprite* QuartzBlock::getTexture(const Direction*, const BlockState* state) {}

// NON_MATCHING: static initalizer is different than target
BlockStateDefinition* QuartzBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}

not_null_ptr<ItemInstance> QuartzBlock::getSilkTouchItemInstance(const BlockState* state) {
    Variant* variant = state->getValue<Variant*>(VARIANT);
    return variant != Variant::LINES_X && variant != Variant::LINES_Z ?
               Block::getSilkTouchItemInstance(state) :
               new ItemInstance(Item::byBlock(this), 1, Variant::LINES_Y->getData());
}

const BlockState* QuartzBlock::getStateForPlacement(Level* level, const BlockPos& pos,
                                                    const Direction* direction, float, float, float, int data,
                                                    std::shared_ptr<LivingEntity>) {
    if (data == Variant::LINES_Y->getData()) {
        switch (direction->getAxis()->getId()) {
        case 2:
            return this->defaultBlockState()->setValue(VARIANT, Variant::LINES_Z);
        case 0:
            return this->defaultBlockState()->setValue(VARIANT, Variant::LINES_X);
        case 1:
        default:  // it took me so long to figure that this is like 2 cases so weird
            return this->defaultBlockState()->setValue(VARIANT, Variant::LINES_Y);
        }
    } else if (data == Variant::CHISELED->getData()) {
        return this->defaultBlockState()->setValue(VARIANT, Variant::CHISELED);
    } else {
        return this->defaultBlockState()->setValue(VARIANT, Variant::DEFAULT);
    }
}
