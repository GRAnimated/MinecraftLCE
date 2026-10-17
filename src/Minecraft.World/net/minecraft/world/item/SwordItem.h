#pragma once

#include "net/minecraft/world/item/Item.h"

class SwordItem : public Item {
public:
    SwordItem(const Item::Tier*);
    void* m_unknown[1];
};
