#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/world/item/CoalItem.h"
#include "net/minecraft/world/item/ItemInstance.h"

CoalItem::CoalItem() {
    this->setStackedByData(true);
    this->setMaxDamage(0);
}

int CoalItem::getDescriptionId(not_null_ptr<ItemInstance> itemInstance) {
    if (itemInstance->getAuxValue() == 1)
        return 0xF0997BAF;
    else
        return 0x1EC60CB7;
}

void CoalItem::registerIcons(IconRegister* iconRegister) {
    Item::registerIcons(iconRegister);

    this->mCharcoalIcon = iconRegister->registerIcon(L"charcoal");
}

TextureAtlasSprite* CoalItem::getIcon(int auxValue) {
    if (auxValue == 1)
        return this->mCharcoalIcon;
    else
        return Item::getIcon(auxValue);
}
