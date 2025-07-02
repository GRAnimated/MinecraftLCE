#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/item/DiggerItem.h"

class AxeItem : public DiggerItem {
public:
    static arrayWithLength<Block*> DIGGABLES;

    static void staticCtor();

    AxeItem(const Item::Tier*);

    ~AxeItem() override;
    float getDestroySpeed(not_null_ptr<ItemInstance>, BlockState*) override;
};