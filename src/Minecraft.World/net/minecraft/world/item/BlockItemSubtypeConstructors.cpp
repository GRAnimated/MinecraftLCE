#include "net/minecraft/world/item/ItemBootstrapTypes.h"

SlabBlockItem::SlabBlockItem(Block* block, HalfSlabBlock* halfSlab, HalfSlabBlock* fullSlab)
    : BlockItem(block), m_halfSlab(halfSlab), m_fullSlab(fullSlab) {
    setMaxDamage(0);
    setStackedByData(true);
}

MultiBlockItem::MultiBlockItem(Block* block, Block* secondaryBlock,
                               unsigned int (*nameResolver)(not_null_ptr<ItemInstance>),
                               unsigned int (*descriptionResolver)(not_null_ptr<ItemInstance>))
    : BlockItem(block), m_secondaryBlock(secondaryBlock), m_nameResolver(nameResolver),
      m_descriptionResolver(descriptionResolver) {
    setMaxDamage(0);
    setStackedByData(true);
}

TintedBlockItem::TintedBlockItem(Block* block, bool stackedByData) : BlockItem(block) {
    if (stackedByData) {
        setMaxDamage(0);
        setStackedByData(true);
    }
}

LeafBlockItem::LeafBlockItem(Block* block) : BlockItem(block), m_leavesBlock(block) {
    setMaxDamage(0);
    setStackedByData(true);
}

PistonBlockItem::PistonBlockItem(Block* block) : BlockItem(block) {}

SnowItem::SnowItem(Block* block) : BlockItem(block) {
    setMaxDamage(0);
    setStackedByData(true);
}

ShulkerBoxBlockItem::ShulkerBoxBlockItem(Block* block) : BlockItem(block) {
    setMaxStackSize(1);
}

WaterLilyBlockItem::WaterLilyBlockItem(Block* block) : TintedBlockItem(block, false) {}

void Item::setStackedByData(bool stackedByData) {
    m_stackedByData = stackedByData;
}
