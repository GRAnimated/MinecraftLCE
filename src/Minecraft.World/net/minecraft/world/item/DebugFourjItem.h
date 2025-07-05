#pragma once

#include "net/minecraft/world/item/Item.h"
#include "types.h"

class DebugFourjItem : public Item {
    DebugFourjItem();

    ~DebugFourjItem() override;
    bool interactEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, std::shared_ptr<LivingEntity>,
                       InteractionHand::EInteractionHand) override;
};
