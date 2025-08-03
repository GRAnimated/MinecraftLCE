#pragma once

#include "net/minecraft/world/level/block/LogBlock.h"
#include "net/minecraft/world/level/block/PlanksBlock.h"
#include "types.h"

class OldLogBlock : public LogBlock {
public:
    static void blockStaticCtor();

    OldLogBlock();

    static inline EnumProperty<PlanksBlock::Variant*>* VARIANT;

    const MaterialColor* getMapColor(const BlockState*, LevelSource*, const BlockPos&) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    not_null_ptr<ItemInstance> getSilkTouchItemInstance(const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    int getWoodType(const BlockState* state) override;
};
