#include "net/minecraft/world/level/levelgen/feature/EndPodiumFeature.h"

#include "net/minecraft/core/BlockPosIterator.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/TorchBlock.h"

extern double endDistanceToSpawn(const Vec3i*, int, int, int);

// name guessed
EndPodiumFeature::EndPodiumFeature(bool active) : Feature(false), m_active(active) {}

// name guessed
// NON_MATCHING | score: 2441 (lower is better)
bool EndPodiumFeature::place(Level* level, Random&, const BlockPos& pos) {
    BlockPos lower(pos.getX() - 4, pos.getY() - 1, pos.getZ() - 4);
    BlockPos upper(pos.getX() + 4, pos.getY() + 32, pos.getZ() + 4);
    BlockPosIterator* iterator = BlockPos::between(lower, upper);
    while (iterator->hasNext()) {
        BlockPos* candidate = iterator->next();
        double distance = endDistanceToSpawn(candidate, pos.getX(), candidate->getY(), pos.getZ());
        if (distance <= 3.5) {
            if (candidate->getY() < pos.getY()) {
                if (distance <= 2.5)
                    setBlock(level, *candidate, Blocks::BEDROCK->defaultBlockState());
                else if (candidate->getY() < pos.getY())
                    setBlock(level, *candidate, Blocks::END_STONE->defaultBlockState());
            } else if (candidate->getY() > pos.getY()) {
                setBlock(level, *candidate, Blocks::AIR->defaultBlockState());
            } else if (distance > 2.5) {
                setBlock(level, *candidate, Blocks::BEDROCK->defaultBlockState());
            } else {
                setBlock(level, *candidate,
                         (m_active ? Blocks::END_PORTAL : Blocks::AIR)->defaultBlockState());
            }
        }
    }
    // The original placement does not delete this iterator.
    setBlock(level, pos.above(0), Blocks::BEDROCK->defaultBlockState());
    setBlock(level, pos.above(1), Blocks::BEDROCK->defaultBlockState());
    setBlock(level, pos.above(2), Blocks::BEDROCK->defaultBlockState());
    setBlock(level, pos.above(3), Blocks::BEDROCK->defaultBlockState());
    BlockPos torchLevel = pos.above(2);
    auto directions = Direction::Plane::HORIZONTAL->iterator();
    for (unsigned int i = 0; i < directions.m_length; ++i) {
        const Direction* direction = directions[i];
        setBlock(level, torchLevel.relative(direction),
                 Blocks::TORCH->defaultBlockState()->setValue(TorchBlock::FACING, direction));
    }
    return true;
}
