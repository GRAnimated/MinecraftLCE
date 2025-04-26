#include "types.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentHelper.h"
#include "Minecraft.World/enchantment/categories/ChestArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/ThornsEnchantment.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/item/ArmorItem.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/level/DamageSource.h"
#include <memory>

ThornsEnchantment::ThornsEnchantment(const Rarity* rarity,
                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, ChestArmorCategory::sChestArmorCategory, equipmentSlots) {
    this->setDescriptionId(0x88507D2E);
}

int ThornsEnchantment::getMaxLevel() {
    return 3;
}
int ThornsEnchantment::getMinCost(int a2) {
    return 20 * a2 - 10;
}
int ThornsEnchantment::getMaxCost(int a2) {
    return Enchantment::getMinCost(a2) + 50;
}
bool ThornsEnchantment::canEnchant(not_null_ptr<ItemInstance> const& itemInstance) {
    return dynamic_cast<const ArmorItem*>(itemInstance->getItem()) ?
               true :
               Enchantment::canEnchant(not_null_ptr<ItemInstance>(itemInstance));
}
// NON_MATCHING: this is std::shared_ptr hell
void ThornsEnchantment::doPostHurt(const std::shared_ptr<LivingEntity>& receiver,
                                   const std::shared_ptr<Entity>& attacker, int a4) {
    Random* random = receiver->getRandom();
    // TODO: LATER REPLACE WITH PROPER ENCHANTMENT THAT GETS INITALIZED IN Enchantments::staticCtor
    std::shared_ptr<ItemInstance> item = EnchantmentHelper::getRandomItemWith(nullptr, receiver);

    if (shouldHit(a4, random)) {
        if (attacker.get()) {
            attacker->hurt(DamageSource::CreateThorns(receiver), getDamage(a4, random));
        }

        if (!item->isEmpty()) {
            item->hurtAndBreak(3, receiver);
        }
    } else if (!item->isEmpty()) {
        item->hurtAndBreak(1, receiver);
    }
}