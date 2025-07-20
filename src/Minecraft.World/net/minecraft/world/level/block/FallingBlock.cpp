#include "net/minecraft/world/level/block/FallingBlock.h"

#include "net/minecraft/core/particles/ParticleTypes.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/entity/item/FallingBlockEntity.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/chunk/ChunkGenerator.h"
#include "net/minecraft/world/level/material/Material.h"
#include <memory>

FallingBlock::FallingBlock() : Block(Material::SAND) {
    this->field_A0 = 11;
}

FallingBlock::FallingBlock(Material* material) : Block(material) {
    this->field_A0 = 11;
}

bool FallingBlock::isFree(const BlockState* state) {
    Block* block = state->getBlock();  // why??
    Material* material = state->getMaterial();
    return block == Blocks::FIRE || material == Material::AIR || material == Material::WATER
           || material == Material::LAVA;
}

void FallingBlock::checkSlide(Level* level, const BlockPos& pos) {
    if (this->isFree(level->getBlockState(pos.below())) && pos.getY() >= 0) {
        if (ChunkGenerator::inPostProcessStep
            || !level->hasChunkAt(pos.offset(-32, -32, -32), pos.offset(32, 32, 32))) {
            level->removeBlock(pos);
            BlockPos tempPos = pos;
            for (tempPos = pos.below(); isFree(level->getBlockState(tempPos)) && tempPos.getY() > 0;
                 tempPos = tempPos.below()) {
            }

            if (tempPos.getY() > 0) {
                level->setBlockAndUpdate(tempPos.above(), this->defaultBlockState());
            }
        } else if (!level->mIsLocal) {
            if (level->newFallingBlockAllowed()) {
                std::shared_ptr<FallingBlockEntity> blockEnt
                    = std::shared_ptr<FallingBlockEntity>(new FallingBlockEntity(
                        level, pos.getX() + 0.5, pos.getY(), pos.getZ() + 0.5, level->getBlockState(pos)));
                this->falling(blockEnt);
                level->addEntity(blockEnt);
            } else {
                level->forceAddBlockTick(pos, this, this->getTickDelay(level), 0);
            }
        }
    }
}

void FallingBlock::tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) {
    if (!level->mIsLocal)
        this->checkSlide(level, pos);
}

void FallingBlock::animateTick(const BlockState* blockState, Level* level, const BlockPos& pos,
                               Random* random) {
    if (random->nextInt(16) == 0) {
        BlockPos blockpos = pos.below();

        if (isFree(level->getBlockState(blockpos))) {
            double x = pos.getX() + random->nextFloat();
            double y = pos.getY() - 0.05;
            double z = pos.getZ() + random->nextFloat();
            arrayWithLength<int> blockData(1, true);
            blockData[0] = Block::getIdWithData(blockState);
            level->addParticle(ParticleTypes::FALLING_DUST, x, y, z, 0.0, 0.0, 0.0, blockData);
            delete blockData.data;
        }
    }
}

void FallingBlock::neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                                   const BlockPos& neighborPos) {
    level->addToTickNextTick(pos, this, this->getTickDelay(level));
}

int FallingBlock::getTickDelay(Level* level) {
    return 2;
}

void FallingBlock::onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) {
    level->addToTickNextTick(pos, this, this->getTickDelay(level));
}

void FallingBlock::falling(std::shared_ptr<FallingBlockEntity>) {}

void FallingBlock::onLand(Level*, const BlockPos&, const BlockState*, const BlockState*) {}

void FallingBlock::onBroken(Level*, const BlockPos&) {}

int FallingBlock::getDustColor(const BlockState*) {
    return 0xFF000000;
}
