#include "net/minecraft/world/item/HorseArmorItem.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/util/Color.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "types.h"

std::wstring sBaseTierName = L"leather_horse_armor_base";
std::wstring sColorTagName = L"customColor";

HorseArmorItem::HorseArmorItem(int tier, int protection, int textureId, const wchar_t* hashName)
    : mTier(tier) {
    mProtection = protection;
    mTextureIds.push_back(textureId);

    mHashName = hashName;
    mDefaultIcon = nullptr;
    mBaseTierIcon = nullptr;
}

HorseArmorItem::HorseArmorItem(int tier, int protection, const int* textureIds, int textureIdCount,
                               const wchar_t* hashName)
    : mTier(tier) {
    mProtection = protection;
    for (int i = 0; i < textureIdCount; i++) {
        mTextureIds.push_back(textureIds[i]);
    }

    mHashName = hashName;
    mDefaultIcon = nullptr;
    mBaseTierIcon = nullptr;
}

HorseArmorItem::HorseArmorItem(int tier, int protection) : mTier(tier) {
    mProtection = protection;
    mTextureIds.push_back(-1);

    mHashName = L"";
    mDefaultIcon = nullptr;
    mBaseTierIcon = nullptr;
}

int HorseArmorItem::getColor(not_null_ptr<ItemInstance> itemInstance, int auxValue) {
    if (auxValue != 0)
        return Color(255, 255, 255).getRGB();

    return getDyedColor(itemInstance);
}

void HorseArmorItem::registerIcons(IconRegister* iconRegister) {
    mDefaultIcon = iconRegister->registerIcon(getIconName());
    if (getTier() == 1)
        mBaseTierIcon = iconRegister->registerIcon(sBaseTierName);
}

bool HorseArmorItem::hasMultipleSpriteLayers() {
    return true;
}

// NON_MATCHING: Extra parameter passed into Item::getLayerIcon, I'm not sure how to not pass a third
// variable in without changing the symbol
TextureAtlasSprite* HorseArmorItem::getLayerIcon(int auxValue, int layer) {
    int tier = getTier();
    if (layer != 0 || tier != 1)
        return Item::getLayerIcon(auxValue, auxValue);

    return mBaseTierIcon;
}

TextureAtlasSprite* HorseArmorItem::getIcon(int auxValue) {
    return mDefaultIcon;
}

size_t HorseArmorItem::getTextureCount() const {
    return mTextureIds.end() - mTextureIds.begin();
}

int HorseArmorItem::getTexture(int textureId) const {
    return mTextureIds.at(textureId);
}
std::wstring HorseArmorItem::getHash() const {
    return mHashName;
}

int HorseArmorItem::getTier() const {
    return mTier;
}

int HorseArmorItem::getDyedColor(not_null_ptr<ItemInstance> itemInstance) const {
    if (getTier() == 1) {
        ItemInstance* instance = itemInstance.get();
        int fallbackColor = 0xA06540;
        if (instance->hasTag()) {
            CompoundTag* tag = instance->getTag();
            if (tag->contains(sColorTagName))
                return tag->getInt(sColorTagName);
        }
        return fallbackColor;
    }

    return Color(255, 255, 255).getRGB();
}

bool HorseArmorItem::hasCustomColor(const not_null_ptr<ItemInstance>& itemInstance) {
    ItemInstance* instance = itemInstance.get();
    if (!instance->hasTag())
        return false;

    CompoundTag* tag = instance->getTag();
    return tag->contains(sColorTagName);
}

void HorseArmorItem::clearColor(const not_null_ptr<ItemInstance>& itemInstance) {
    ItemInstance* instance = itemInstance.get();
    if (!instance->hasTag())
        return;

    CompoundTag* tag = instance->getTag();
    tag->remove(sColorTagName);
}

void HorseArmorItem::setColor(const not_null_ptr<ItemInstance>& itemInstance, int color) {
    ItemInstance* instance = itemInstance.get();
    if (!itemInstance->hasTag()) {
        instance->setTag(new CompoundTag());
        instance = itemInstance.get();
    }
    instance->getTag()->putInt(sColorTagName, color);
}
