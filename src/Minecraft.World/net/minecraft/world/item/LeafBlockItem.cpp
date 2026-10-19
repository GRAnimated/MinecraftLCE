#include "net/minecraft/world/item/ItemBootstrapTypes.h"

// name guessed
LeafBlockItem::LeafBlockItem(Block* block) : BlockItem(block), m_leavesBlock(block) {
    setMaxDamage(0);
    setStackedByData(true);
}
