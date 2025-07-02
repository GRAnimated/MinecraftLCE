#include "types.h"
#include "Minecraft.World/item/Item.h"

class CoalItem : public Item {
    CoalItem();

    int getDescriptionId(not_null_ptr<ItemInstance> itemInstance) override;
    void registerIcons(IconRegister* iconRegister) override;
    TextureAtlasSprite* getIcon(int auxValue) override;

    TextureAtlasSprite* mCharcoalIcon;
};