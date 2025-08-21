#pragma once

#include "net/minecraft/world/item/ComplexItem.h"

class EmptyMapItem : public ComplexItem {
public:
    EmptyMapItem();

    InteractionResultHolder use(Level* level, std::shared_ptr<Player> user,
                                InteractionHand::EInteractionHand hand) override;
    unsigned int GetUseTooltip(const ItemToolTipDataHolder& toolTipDataHolder) override;
};
