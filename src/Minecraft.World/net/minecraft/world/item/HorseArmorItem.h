#pragma once

#include "net/minecraft/world/item/Item.h"
#include <vector>

class HorseArmorItem : public Item {
public:
    HorseArmorItem(int tier, int protection, int textureId, const wchar_t* hashName);
    HorseArmorItem(int tier, int protection, const int* textureIds, int textureIdCount,
                   const wchar_t* hashName);
    HorseArmorItem(int tier, int protection);

    ~HorseArmorItem() override {}

    int getColor(not_null_ptr<ItemInstance> itemInstance, int auxValue) override;
    void registerIcons(IconRegister* iconRegister) override;
    bool hasMultipleSpriteLayers() override;
    TextureAtlasSprite* getLayerIcon(int auxValue, int layer) override;
    TextureAtlasSprite* getIcon(int auxValue) override;
    size_t getTextureCount() const;
    int getTexture(int) const;
    std::wstring getHash() const;
    int getTier() const;
    int getDyedColor(not_null_ptr<ItemInstance> itemInstance) const;
    bool hasCustomColor(const not_null_ptr<ItemInstance>& itemInstance);
    void clearColor(const not_null_ptr<ItemInstance>& itemInstance);
    void setColor(const not_null_ptr<ItemInstance>& itemInstance, int color);

    TextureAtlasSprite* mBaseTierIcon;
    int mTier;
    std::vector<int> mTextureIds;
    std::wstring mHashName;
    int mProtection;
};
