#include "net/minecraft/world/item/CoalItem.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/world/item/ItemInstance.h"

CoalItem::CoalItem() {
    this->setStackedByData(true);
    this->setMaxDamage(0);
}

unsigned int CoalItem::getDescriptionId(not_null_ptr<ItemInstance> itemInstance) {
    if (itemInstance->getAuxValue() == 1)
        return StringIDs::Charcoal;
    else
        return StringIDs::Coal;
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
