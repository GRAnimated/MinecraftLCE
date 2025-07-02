#pragma once

#include "Minecraft.World/level/block/Block.h"

// Yes, 4J really named this class Glowstoneblock and not GlowstoneBlock.
// I've chosen to not name the file like that because it looks ugly.
class Glowstoneblock : public Block {
public:
    Glowstoneblock(Material* material);

    MaterialColor* getMapColor(const BlockState* blockState, LevelSource* levelSource,
                               const BlockPos& pos) override;
    int getResourceCount(Random*) override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
    int getResourceCountForLootBonus(int, Random*) override;
};
