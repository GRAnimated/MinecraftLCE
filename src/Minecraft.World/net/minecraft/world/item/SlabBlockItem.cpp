#include "net/minecraft/world/item/ItemBootstrapTypes.h"

// name guessed
SlabBlockItem::SlabBlockItem(Block* block, HalfSlabBlock* halfSlab, HalfSlabBlock* fullSlab)
    : BlockItem(block), m_halfSlab(halfSlab), m_fullSlab(fullSlab) {
    setMaxDamage(0);
    setStackedByData(true);
}
