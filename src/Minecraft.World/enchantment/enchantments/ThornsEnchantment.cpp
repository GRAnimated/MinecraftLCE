#include "types.h"
#include "Minecraft.World/Random.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/EnchantmentHelper.h"
#include "Minecraft.World/enchantment/Enchantments.h"
#include "Minecraft.World/enchantment/categories/ChestArmorCategory.h"
#include "Minecraft.World/enchantment/enchantments/ThornsEnchantment.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/item/ArmorItem.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/level/DamageSource.h"
#include "Minecraft.World/sounds/SoundEvents.h"
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
bool ThornsEnchantment::canEnchant(const not_null_ptr<ItemInstance>& itemInstance) {
    return dynamic_cast<const ArmorItem*>(itemInstance->getItem()) ?
               true :
               Enchantment::canEnchant(not_null_ptr<ItemInstance>(itemInstance));
}

void ThornsEnchantment::doPostHurt(const std::shared_ptr<LivingEntity>& receiver,
                                   const std::shared_ptr<Entity>& attacker, int a4) {
    Random* random = receiver->getRandom();
    std::shared_ptr<ItemInstance> item = EnchantmentHelper::getRandomItemWith(Enchantments::THORNS, receiver);

    if (shouldHit(a4, random)) {
        if (attacker.get()) {
            DamageSource* damage = DamageSource::CreateThorns(receiver);
            attacker->hurt(damage, getDamage(a4, random));
            delete damage;

            attacker->playSound(SoundEvents::ENCHANT_THORNS_HIT, 0.5f, 1.0f);
        }

        if (!item->isEmpty()) {
            item->hurtAndBreak(3, receiver);
        }
    } else if (!item->isEmpty()) {
        item->hurtAndBreak(1, receiver);
    }
}