#pragma once

#include "net/minecraft/world/item/Item.h"
#include "types.h"

class ElytraItem_ItemPropertyFunction : public ItemPropertyFunction {
    void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>) override;
};

class ElytraItem : public Item {
public:
    ElytraItem();

    static bool isFlyEnabled(not_null_ptr<ItemInstance>);

    unsigned int GetUseTooltip(const ItemToolTipDataHolder&) override;
    ~ElytraItem() override;
    bool TestUse(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) override;
    InteractionResultHolder use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) override;
    bool isValidRepairItem(not_null_ptr<ItemInstance>, not_null_ptr<ItemInstance>) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getLayerIcon(int, int) override;
    TextureAtlasSprite* getIcon(not_null_ptr<ItemInstance>) override;
    int GetArmorType() override;

    TextureAtlasSprite* mBrokenElytraIcon;
};
