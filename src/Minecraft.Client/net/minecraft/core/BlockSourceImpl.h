#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/BlockSource.h"

class BlockSourceImpl : public BlockSource {
public:
    BlockSourceImpl(Level* level, const BlockPos& pos);

    double getX() override;
    double getY() override;
    double getZ() override;
    ~BlockSourceImpl() override {}
    BlockPos getPos() override;
    const BlockState* getBlockState() override;
    Material* getMaterial() override;
    std::shared_ptr<BlockEntity> getEntity() override;
    Level* getWorld() override;

    Level* mLevel;
    BlockPos mPos;
};
