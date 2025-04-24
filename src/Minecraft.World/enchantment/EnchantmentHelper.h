#pragma once

#include "types.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include <memory>

class ItemInstance;
class Enchantment;

class EnchantmentHelper {
public:
    static int getItemEnchantmentLevel(const Enchantment*, not_null_ptr<ItemInstance> const&);
    static std::shared_ptr<ItemInstance> getRandomItemWith(const Enchantment*, std::shared_ptr<LivingEntity>);
};