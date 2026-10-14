#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/item/BlockItem.h"
#include "net/minecraft/world/item/Item.h"

Item* Item::setBaseItemTypeAndMaterial(int type, int material) {
    m_baseItemType = type;
    m_material = material;
    return this;
}

Item* Item::setDescriptionId(int name) {
    m_descriptionId = name;
    return this;
}

Item* Item::setUseDescriptionId(int description) {
    m_useDescriptionId = description;
    return this;
}

Item* Item::setDescriptionId(int name, int description) {
    return setDescriptionId(name)->setUseDescriptionId(description);
}

Item* Item::setCraftingRemainingItem(Item* item) {
    m_craftingRemainingItem = item;
    return this;
}

Item* Item::setMaxStackSize(int size) {
    m_maxStackSize = size;
    return this;
}

Item* Item::setHandEquipped() {
    m_handEquipped = true;
    return this;
}

Item* Item::setFlag78(bool value) {
    m_byte78 = value;
    return this;
}

void Item::registerItem(int id, const std::wstring& name, Item* item) {
    ResourceLocation key(name);
    registerItem(id, key, item);
}
