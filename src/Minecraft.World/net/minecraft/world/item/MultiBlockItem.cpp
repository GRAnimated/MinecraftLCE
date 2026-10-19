#include "net/minecraft/world/item/ItemBootstrapTypes.h"

// name guessed
MultiBlockItem::MultiBlockItem(Block* block, Block* secondaryBlock,
                               unsigned int (*nameResolver)(not_null_ptr<ItemInstance>),
                               unsigned int (*descriptionResolver)(not_null_ptr<ItemInstance>))
    : BlockItem(block), m_secondaryBlock(secondaryBlock), m_nameResolver(nameResolver),
      m_descriptionResolver(descriptionResolver) {
    setMaxDamage(0);
    setStackedByData(true);
}
