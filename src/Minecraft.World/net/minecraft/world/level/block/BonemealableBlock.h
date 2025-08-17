#pragma once

class Level;
class BlockPos;
class BlockState;
class Random;

class BonemealableBlock {
public:
    virtual bool isValidBonemealTarget(Level*, const BlockPos&, const BlockState*, bool) = 0;
    virtual bool isBonemealSuccess(Level*, Random*, const BlockPos&, const BlockState*) = 0;
    virtual void performBonemeal(Level*, Random*, const BlockPos&, const BlockState*) = 0;
};
