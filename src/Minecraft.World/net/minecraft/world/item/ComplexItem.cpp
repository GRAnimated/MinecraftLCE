#include "ComplexItem.h"
#include "net/minecraft/world/item/Item.h"

ComplexItem::ComplexItem() : Item() {}

std::shared_ptr<Packet> ComplexItem::getUpdatePacket(not_null_ptr<ItemInstance>, Level*,
                                                     std::shared_ptr<Player>) {
    return nullptr;
}
