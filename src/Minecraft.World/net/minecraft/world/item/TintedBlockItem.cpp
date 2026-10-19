#include "net/minecraft/world/effect/MobEffectInstance.h"

#include "net/minecraft/world/item/ItemBootstrapTypes.h"

TintedBlockItem::TintedBlockItem(Block* block, bool stackedByData) : BlockItem(block) {
    if (stackedByData) {
        setMaxDamage(0);
        setStackedByData(true);
    }
}

// name guessed
TintedBlockItem* TintedBlockItem::setDescriptionIds(arrayWithLength<int> ids) {
    m_descriptionIds = arrayWithLength<int>(ids.m_length, true);
    for (unsigned int i = 0; i < ids.m_length; ++i)
        m_descriptionIds[i] = ids[i];
    return this;
}
