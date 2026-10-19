#include "net/minecraft/world/item/ItemBootstrapTypes.h"

// name guessed
SnowItem::SnowItem(Block* block) : BlockItem(block) {
    setMaxDamage(0);
    setStackedByData(true);
}
