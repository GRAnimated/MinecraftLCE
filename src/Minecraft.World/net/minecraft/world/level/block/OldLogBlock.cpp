#include "net/minecraft/world/level/block/OldLogBlock.h"

#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

static bool oldlog_filter(PlanksBlock::Variant* variant) {
    return variant->getData() < 4;
}

void OldLogBlock::blockStaticCtor() {
    OldLogBlock::VARIANT = EnumProperty<PlanksBlock::Variant*>::create(
        L"variant", typeid(PlanksBlock::Variant), PlanksBlock::Variant::VARIANTS,
        Predicates<PlanksBlock::Variant*>::FunctionPredicate::createPredicate(oldlog_filter));
}

OldLogBlock::OldLogBlock() : LogBlock() {
    Block::DerivedInit();
    const BlockState* defaultState = this->mBlockStateDefinition->any()
                                         ->setValue(OldLogBlock::VARIANT, PlanksBlock::Variant::OAK)
                                         ->setValue(LogBlock::LOG_AXIS, LogBlock::LogAxis::Y);
    this->registerDefaultState(defaultState);
}

// NON_MATCHING: not sure, logic should be preserved
const MaterialColor* OldLogBlock::getMapColor(const BlockState* state, LevelSource*, const BlockPos&) {
    PlanksBlock::Variant* variant = state->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT);
    LogBlock::LogAxis* log_axis = state->getValue<LogBlock::LogAxis*>(LogBlock::LOG_AXIS);

    if (log_axis->getId() == 1) {
        return variant->getMaterialColor();
    }

    int data = variant->getData();
    if (data == 1)
        return PlanksBlock::Variant::DARK_OAK->getMaterialColor();
    if (data == 2)
        return MaterialColor::QUARTZ;

    return PlanksBlock::Variant::SPRUCE->getMaterialColor();
}

// NON_MATCHING: have no clue
const BlockState* OldLogBlock::getBlockState(int data) {
    const BlockState* state = this->defaultBlockState()->setValue(OldLogBlock::VARIANT, (data & 3));
    LogBlock::LogAxis* axis;

    if ((data & 0xC) == 0x4) {
        axis = LogBlock::LogAxis::X;
    } else if ((data & 0xC) == 0x0) {
        axis = LogBlock::LogAxis::Y;
    } else if ((data & 0xC) == 0x8) {
        axis = LogBlock::LogAxis::Z;
    } else {
        axis = LogBlock::LogAxis::NONE;
    }

    return state->setValue(LogBlock::LOG_AXIS, axis);
}

int OldLogBlock::convertBlockStateToLegacyData(const BlockState* state) {
    int planksData = state->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT)->getData();
    int logData = state->getValue<LogBlock::LogAxis*>(LogBlock::LOG_AXIS)->getId();

    int result = planksData;
    if (logData == 0)
        result = planksData | 4;
    else if (logData == 3)
        result = planksData | 12;
    else if (logData == 2)
        result = planksData | 8;

    return result;
}

int OldLogBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT)->getData();
}

not_null_ptr<ItemInstance> OldLogBlock::getSilkTouchItemInstance(const BlockState* state) {
    return new ItemInstance(Item::byBlock(this), 1,
                            state->getValue<PlanksBlock::Variant*>(OldLogBlock::VARIANT)->getData());
}

// NON_MATCHING
BlockStateDefinition* OldLogBlock::createBlockStateDefinition() {
    static const Property* properties[] = {VARIANT, LOG_AXIS};
    return new BlockStateDefinition(this, properties);
}

int OldLogBlock::getWoodType(const BlockState* state) {
    return state->getValue<PlanksBlock::Variant*>(VARIANT)->getData();
}
