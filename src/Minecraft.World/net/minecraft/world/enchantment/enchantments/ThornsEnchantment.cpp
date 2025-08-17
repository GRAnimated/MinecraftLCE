#include "net/minecraft/world/enchantment/enchantments/ThornsEnchantment.h"

#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/enchantment/categories/ChestArmorCategory.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/item/ArmorItem.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/EnchantmentHelper.h"
#include "net/minecraft/world/item/enchantment/Enchantments.h"
#include "types.h"
#include <memory>

ThornsEnchantment::ThornsEnchantment(const Rarity* rarity,
                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, ChestArmorCategory::sChestArmorCategory, equipmentSlots) {
    this->setDescriptionId(StringIDs::Thorns);
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
