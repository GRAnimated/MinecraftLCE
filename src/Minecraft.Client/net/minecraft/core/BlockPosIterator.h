#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Iterator.h"

class BlockPosIterator : public Iterator<BlockPos*> {
public:
    BlockPosIterator(const BlockPos&, const BlockPos&);

    bool hasNext() override;
    BlockPos* next() override;
};
