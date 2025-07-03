#pragma once

#include "types.h"
#include "net/minecraft/world/item/Item.h"
class DebugFourjItem : public Item {
    DebugFourjItem();

    ~DebugFourjItem() override;
    bool interactEnemy(not_null_ptr<ItemInstance>, std::shared_ptr<Player>, std::shared_ptr<LivingEntity>,
                       InteractionHand::EInteractionHand) override;
};
