#include "net/minecraft/world/item/BlockItem.h"
#include "net/minecraft/world/level/block/Block.h"

BlockItem::BlockItem(Block* block) : m_block(block), m_unknown88(nullptr) {}

Block* BlockItem::getBlock() {
    return m_block;
}

unsigned int BlockItem::getDescriptionId(int data) {
    return m_block->getDescriptionId(data);
}

unsigned int BlockItem::getDescriptionId(not_null_ptr<ItemInstance>) {
    return m_block->getDescriptionId(-1);
}

unsigned int BlockItem::getUseDescriptionId() {
    return m_block->getUseDescriptionId();
}

unsigned int BlockItem::getUseDescriptionId(not_null_ptr<ItemInstance>) {
    return m_block->getUseDescriptionId();
}
