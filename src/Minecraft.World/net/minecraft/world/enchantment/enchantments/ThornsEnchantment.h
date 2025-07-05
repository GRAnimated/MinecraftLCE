#pragma once

#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include <memory>

class ThornsEnchantment : public Enchantment {
public:
    ThornsEnchantment(const Rarity*, arrayWithLength<const EquipmentSlot*>);

    static bool shouldHit(int, Random*);
    static int getDamage(int, Random*);

    int getMaxLevel() override;
    int getMinCost(int) override;
    int getMaxCost(int) override;
    bool canEnchant(const not_null_ptr<ItemInstance>&) override;
    void doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) override;
};
