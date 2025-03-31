#pragma once
#include "Minecraft.World/item/Item.h"

class Arrow;

class ArrowItem : public Item {
public:
	virtual std::shared_ptr<Arrow> createArrow(Level*, const std::shared_ptr<ItemInstance>&, const std::shared_ptr<LivingEntity>&);
};