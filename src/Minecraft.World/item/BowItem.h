#pragma once
#include <memory>
#include "Minecraft.World/item/Item.h"

class Player;
class ItemInstance;

class BowItem : public Item{
public:
    static const not_null_ptr<ItemInstance>& findProjectile(const std::shared_ptr<Player>&);
};