#pragma once

#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/material/MaterialColor.h"

class OreBlock : public Block {
public:
    OreBlock();
    OreBlock(const MaterialColor*);

    ~OreBlock() override {}
    int getResourceCount(Random*) override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
    void spawnResources(Level* level, const BlockPos& pos, const BlockState* blockState, float chance,
                        int fortuneLevel) override;
    int getResourceCountForLootBonus(int, Random*) override;
    not_null_ptr<ItemInstance> getCloneItemInstance(Level* level, const BlockPos& pos,
                                                    const BlockState* blockState) override;
    int getSpawnResourcesAuxValue(const BlockState* blockState) override;
};
