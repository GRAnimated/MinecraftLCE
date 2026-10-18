#include "net/minecraft/world/level/Level.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include "net/minecraft/world/level/block/state/properties/BlockStateProperties.h"
#include "net/minecraft/world/level/material/Material.h"

// Inferred name for the shared read-only 0.15f threshold at 0x7100e134b8.
extern const float gFreezingTemperature;

bool Level::shouldFreezeIgnoreNeighbors(const BlockPos& pos) {
    return shouldFreeze(pos, false);
}

bool Level::shouldFreezeWithNeighbors(const BlockPos& pos) {
    return shouldFreeze(pos, true);
}

bool Level::isWaterAt(const BlockPos& pos) {
    return getBlockState(pos)->getMaterial() == Material::WATER;
}

bool Level::shouldFreeze(const BlockPos& pos, bool checkNeighbors) {
    // The original b.gt allows an unordered temperature to continue.
    if (getBiome(pos)->getTemperature(&pos) > gFreezingTemperature)
        return false;
    if (pos.getY() >= 0 && pos.getY() < 256 && getBrightness(LightLayer::BLOCK, pos) < 10) {
        const BlockState* state = getBlockState(pos);
        Block* block = state->getBlock();
        if ((block == Blocks::WATER || block == Blocks::FLOWING_WATER)
            && state->getValue<int>(BlockStateProperties::WATER_LEVEL) == 0) {
            if (!checkNeighbors)
                return true;
            if (!isWaterAt(pos.west()) || !isWaterAt(pos.east()) || !isWaterAt(pos.north())
                || !isWaterAt(pos.south()))
                return true;
        }
    }
    return false;
}
