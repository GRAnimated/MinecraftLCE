#pragma once

#include "net/minecraft/world/item/Item.h"

class AirItem : public Item {
public:
    AirItem(Block* block);
    ~AirItem() override {}

    unsigned int getDescriptionId(not_null_ptr<ItemInstance> itemInstance) override;
    void appendHoverText(not_null_ptr<ItemInstance> itemInstance, std::shared_ptr<Player> player,
                         void* htmlString, bool) override;

private:
    Block* mBlock;
};
