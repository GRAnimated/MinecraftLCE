#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/item/Item.h"
#include <memory>
#include <string>

class Player;
class ItemInstance;

class BowItem_Pull_ItemPropertyFunction : ItemPropertyFunction {
public:
    void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>) override;
};

class BowItem_Pulling_ItemPropertyFunction : ItemPropertyFunction {
public:
    void call(not_null_ptr<ItemInstance>, Level*, std::shared_ptr<LivingEntity>) override;
};

class BowItem : public Item {
public:
    BowItem();

    static int GetMaxBowDuration();

    unsigned int GetUseTooltip(const ItemToolTipDataHolder&) override;
    InteractionResultHolder use(Level*, std::shared_ptr<Player>, InteractionHand::EInteractionHand) override;
    int getUseAnimation(not_null_ptr<ItemInstance>) override;
    int getUseDuration(not_null_ptr<ItemInstance>) override;
    void releaseUsing(not_null_ptr<ItemInstance> item, Level* level, std::shared_ptr<LivingEntity> user,
                      int remainingTicks) override;
    int getEnchantmentValue() override;
    void registerIcons(IconRegister*) override;
    int GetOverrideCount() override;
    int GetOverrideCountColour() override;
    TextureAtlasSprite* GetOverrideCountIcon(not_null_ptr<ItemInstance>) override;

    not_null_ptr<ItemInstance> findProjectile(std::shared_ptr<Player>);
    InteractionResultHolder fjUseWithProjectile(Level*, std::shared_ptr<Player>,
                                                InteractionHand::EInteractionHand,
                                                not_null_ptr<ItemInstance>);
    void fjReleaseUsingWithProjectile(not_null_ptr<ItemInstance> bow, Level* level,
                                      std::shared_ptr<LivingEntity> shooter, int remainingTicks,
                                      not_null_ptr<ItemInstance> projectile);
    TextureAtlasSprite* getDrawnIcon(int id);

    static std::wstring BOW_ICON_NAMES[3];

    TextureAtlasSprite* mBowIcons[3];
};
