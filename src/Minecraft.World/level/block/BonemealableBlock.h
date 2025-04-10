#pragma once

class Level;
class BlockPos;
class BlockState;
class Random;

class BonemealableBlock {
public:
    virtual bool isValidBonemealTarget(Level*, BlockPos const&, BlockState const*, bool) = 0;
    virtual bool isBonemealSuccess(Level*, Random*, BlockPos const&, BlockState const*) = 0;
    virtual void performBonemeal(Level*, Random*, BlockPos const&, BlockState const*) = 0;
};
