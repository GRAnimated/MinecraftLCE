#include "Minecraft.World/item/Item.h"
#include "Minecraft.Client/resources/ResourceLocation.h"

// should be replaced with proper ones later on
const ItemPropertyFunction* lefthandedFunction = nullptr;
const ItemPropertyFunction* cooldownFunction = nullptr;

Item::Item() {
    // Some of those should probably be moved to header def but idk which ones
        this->maxStackSize = 64;
        this->maxDamage = 0;
        this->handEquipped = false;
        this->somebool = 0;
        this->craftingRemainingItem = nullptr;
        this->wstring_1 = L"";
        this->baseItemType = 0;
        this->material = 0;
        this->iconName = L"";
        this->icon = nullptr;
        this->byte78 = 0;
    //

    this->simpleRegistry = new SimpleRegistry<ResourceLocation, const ItemPropertyFunction*>();

    this->addProperty(ResourceLocation(L"lefthanded"), lefthandedFunction);

    this->addProperty(ResourceLocation(L"cooldown"), cooldownFunction);
}