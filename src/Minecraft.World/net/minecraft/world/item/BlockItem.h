#pragma once

#include "net/minecraft/world/item/Item.h"

class BlockItem : public Item {
public:
    BlockItem(Block* block);
    ~BlockItem() override;

    Block* getBlock();
    BlockItem* setDescriptionId(unsigned int);
    unsigned int getDescriptionId(int) override;
    unsigned int getDescriptionId(not_null_ptr<ItemInstance>) override;
    unsigned int getUseDescriptionId() override;
    unsigned int getUseDescriptionId(not_null_ptr<ItemInstance>) override;

    Block* m_block;
    void* m_unknown88;
};
