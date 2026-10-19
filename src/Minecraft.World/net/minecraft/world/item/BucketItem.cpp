#include "net/minecraft/world/item/ItemBootstrapTypes.h"
#include "net/minecraft/world/item/LeadItem.h"

// name guessed
BucketItem::BucketItem(Block* block) : m_block(block) {
    m_maxStackSize = 1;
}
