#pragma once

#include "types.h"
#include "Minecraft.World/item/Item.h"

class ElytraItem_ItemPropertyFunction : public ItemPropertyFunction {
    void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>) override;
};

class ElytraItem : public Item {
    ElytraItem();

    static bool isFlyEnabled(not_null_ptr<ItemInstance>);

    int GetUseTooltip(const ItemToolTipDataHolder&) override;
    ~ElytraItem() override;
    bool TestUse(Level*, const std::shared_ptr<Player>&, InteractionHand::EInteractionHand) override;
    InteractionResultHolder use(Level*, const std::shared_ptr<Player>&,
                                InteractionHand::EInteractionHand) override;
    bool isValidRepairItem(const std::shared_ptr<ItemInstance>&,
                           const std::shared_ptr<ItemInstance>&) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getLayerIcon(int, int, const std::shared_ptr<ItemInstance>&) override;
    TextureAtlasSprite* getIcon(not_null_ptr<ItemInstance>) override;
    int GetArmorType() override;

    TextureAtlasSprite* mBrokenElytraIcon;
};