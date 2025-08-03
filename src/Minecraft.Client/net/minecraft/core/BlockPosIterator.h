#include "Iterator.h"
#include "net/minecraft/core/BlockPos.h"

class BlockPosIterator : public Iterator<BlockPos*> {
public:
    BlockPosIterator(const BlockPos&, const BlockPos&);

    virtual bool hasNext() override;
    virtual BlockPos* next() override;
};