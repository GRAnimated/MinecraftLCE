#pragma once

#include "Minecraft.World/item/Item.h"

class BlockItem : public Item {
public:
    BlockItem(Block* block);

    Block* getBlock();
};