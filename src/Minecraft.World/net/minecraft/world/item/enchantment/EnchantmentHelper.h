#pragma once

#include "types.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include <memory>

class ItemInstance;
class Enchantment;

class EnchantmentHelper {
public:
    static int getItemEnchantmentLevel(const Enchantment*, const not_null_ptr<ItemInstance>&);
    static std::shared_ptr<ItemInstance> getRandomItemWith(const Enchantment*,
                                                           const std::shared_ptr<LivingEntity>&);
    static int getDepthStrider(const std::shared_ptr<LivingEntity>&);
};