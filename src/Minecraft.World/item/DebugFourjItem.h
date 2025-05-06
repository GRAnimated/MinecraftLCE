#pragma once

#include "Minecraft.World/item/Item.h"
class DebugFourjItem : public Item {
    DebugFourjItem();

    ~DebugFourjItem() override;
    bool interactEnemy(const std::shared_ptr<ItemInstance>&, const std::shared_ptr<Player>&,
                       const std::shared_ptr<LivingEntity>&, InteractionHand::EInteractionHand) override;
};