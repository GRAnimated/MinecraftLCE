#pragma once

class Block;
class BlockState;

class BlockStateDefinition {
public:
    BlockStateDefinition(Block* block);

    Block* getBlock();
    const BlockState* any();
};
