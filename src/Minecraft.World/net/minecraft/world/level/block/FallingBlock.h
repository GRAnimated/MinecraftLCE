#pragma once

#pragma once

#include "net/minecraft/world/level/block/Block.h"
#include <memory>

class FallingBlockEntity;

class FallingBlock : public Block {
public:
    FallingBlock();
    FallingBlock(Material* material);

    static bool isFree(const BlockState*);

    void checkSlide(Level* level, const BlockPos& pos);

    void tick(Level* level, const BlockPos& pos, const BlockState* blockState, Random*) override;
    void animateTick(const BlockState* blockState, Level* level, const BlockPos& pos, Random*) override;
    void neighborChanged(const BlockState* blockState, Level* level, const BlockPos& pos, Block*,
                         const BlockPos& neighborPos) override;
    int getTickDelay(Level* level) override;
    void onPlace(Level* level, const BlockPos& pos, const BlockState* blockState) override;
    virtual void falling(std::shared_ptr<FallingBlockEntity>);
    virtual void onLand(Level*, const BlockPos&, const BlockState*, const BlockState*);
    virtual void onBroken(Level*, const BlockPos&);
    virtual int getDustColor(const BlockState*);
};