#include "Minecraft.World/item/Item.h"
#include "Minecraft.Client/resources/ResourceLocation.h"

Item::Item() {
    // Those probably should be moved to Item header but idk
        this->maxStackSize = 64;
        this->handEquipped = false;
        this->craftingRemainingItem = nullptr;
        this->baseItemType = 0;
        this->icon = 0;
    //

    this->wstring_1 = L"";
    this->iconName = L"";

    this->simpleRegistry = new SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>();

    // nullptr should be replaced with ItemPropertyFunction object
    this->addProperty(ResourceLocation(L"lefthanded"), nullptr);

    this->addProperty(ResourceLocation(L"cooldown"), nullptr);
}