#pragma once

#pragma once

#include "net/minecraft/world/item/Item.h"
#include "types.h"

class CoalItem : public Item {
    CoalItem();

    unsigned int getDescriptionId(not_null_ptr<ItemInstance> itemInstance) override;
    void registerIcons(IconRegister* iconRegister) override;
    TextureAtlasSprite* getIcon(int auxValue) override;

    TextureAtlasSprite* mCharcoalIcon;
};
