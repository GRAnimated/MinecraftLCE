#pragma once

#include "net/minecraft/world/item/Item.h"
#include <memory>

class Packet;

class ComplexItem : public Item {
public:
    ComplexItem();

    virtual std::shared_ptr<Packet> getUpdatePacket(not_null_ptr<ItemInstance>, Level*,
                                                    std::shared_ptr<Player>);
};
