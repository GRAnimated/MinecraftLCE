#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/NewLogBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

static bool newleaf_predicate(PlanksBlock::Variant* variant) {
    return variant->getData() > 3;
}

void NewLogBlock::blockStaticCtor() {
    NewLogBlock::VARIANT = EnumProperty<PlanksBlock::Variant*>::create(
        L"variant", typeid(PlanksBlock::Variant), PlanksBlock::Variant::VARIANTS,
        Predicates<PlanksBlock::Variant*>::FunctionPredicate::createPredicate(newleaf_predicate));
}

NewLogBlock::NewLogBlock() : LogBlock() {
    Block::DerivedInit();
    const BlockState* defaultState = this->mBlockStateDefinition->any()
                                         ->setValue(NewLogBlock::VARIANT, PlanksBlock::Variant::ACACIA)
                                         ->setValue(LogBlock::LOG_AXIS, LogBlock::LogAxis::Y);
    this->registerDefaultState(defaultState);
}

const MaterialColor* NewLogBlock::getMapColor(const BlockState* state, LevelSource*, const BlockPos&) {
    PlanksBlock::Variant* variant = state->getValue<PlanksBlock::Variant*>(NewLogBlock::VARIANT);
    LogBlock::LogAxis* log_axis = state->getValue<LogBlock::LogAxis*>(LogBlock::LOG_AXIS);
    if (log_axis->getId() == 1) {
        return variant->getMaterialColor();
    }
    if (variant->getData() == 5) {
        return PlanksBlock::Variant::DARK_OAK->getMaterialColor();
    }
    return MaterialColor::STONE;
}

// NON_MATCHING: have no clue
const BlockState* NewLogBlock::getBlockState(int data) {
    const BlockState* state = this->defaultBlockState()->setValue(NewLogBlock::VARIANT, (data & 3) | 4);
    LogBlock::LogAxis* axis = LogBlock::LogAxis::NONE;

    if ((data & 0xC) == 0x4) {
        axis = LogBlock::LogAxis::X;
    } else if ((data & 0xC) == 0x0) {
        axis = LogBlock::LogAxis::Y;
    } else if ((data & 0xC) == 0x8) {
        axis = LogBlock::LogAxis::Z;
    }

    return state->setValue(LogBlock::LOG_AXIS, axis);
}

int NewLogBlock::convertBlockStateToLegacyData(const BlockState* state) {
    int planksData = state->getValue<PlanksBlock::Variant*>(NewLogBlock::VARIANT)->getData() - 4;
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

int NewLogBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<PlanksBlock::Variant*>(NewLogBlock::VARIANT)->getData() - 4;
}

not_null_ptr<ItemInstance> NewLogBlock::getSilkTouchItemInstance(const BlockState* state) {
    return new ItemInstance(Item::byBlock(this), 1,
                            state->getValue<PlanksBlock::Variant*>(NewLogBlock::VARIANT)->getData() - 4);
}

// NON_MATCHING
BlockStateDefinition* NewLogBlock::createBlockStateDefinition() {
    static const Property* properties[] = {VARIANT, LOG_AXIS};
    return new BlockStateDefinition(this, properties);
}

int NewLogBlock::getWoodType(const BlockState* state) {
    return state->getValue<PlanksBlock::Variant*>(VARIANT)->getData();
}