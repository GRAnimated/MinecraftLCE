#pragma once

#include "net/minecraft/world/item/Item.h"

class BlockItem : public Item {
public:
    BlockItem(Block* block);

    Block* getBlock();

    void* m_filler[2];
};
