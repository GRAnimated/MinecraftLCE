#include "net/minecraft/world/item/BlockItem.h"

BlockItem* BlockItem::setDescriptionId(unsigned int name) {
    Item::setDescriptionId(name);
    return this;
}
