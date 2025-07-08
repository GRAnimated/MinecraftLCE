#pragma once

#include "net/minecraft/world/item/Item.h"

class Arrow;

class ArrowItem : public Item {
public:
    ArrowItem();
    ~ArrowItem() override;

    virtual std::shared_ptr<Arrow> createArrow(Level*, const std::shared_ptr<ItemInstance>&,
                                               const std::shared_ptr<LivingEntity>&);
};
