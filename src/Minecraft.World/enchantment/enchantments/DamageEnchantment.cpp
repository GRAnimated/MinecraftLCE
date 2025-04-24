#include "types.h"
#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/enchantment/Enchantment.h"
#include "Minecraft.World/enchantment/categories/WeaponCategory.h"
#include "Minecraft.World/enchantment/enchantments/DamageEnchantment.h"
#include "Minecraft.World/entity/LivingEntity.h"
#include "Minecraft.World/entity/mob/MobEffectInstance.h"
#include "Minecraft.World/entity/mob/MobEffects.h"
#include "Minecraft.World/item/AxeItem.h"
#include "Minecraft.World/item/ItemInstance.h"
#include <memory>

DamageEnchantment::DamageEnchantment(const Rarity* rarity, int type,
                                     arrayWithLength<const EquipmentSlot*> equipmentSlots)
    : Enchantment(rarity, WeaponCategory::sWeaponCategory, equipmentSlots) {
    this->mDamageType = type;
}

int DamageEnchantment::getMaxLevel() {
    return 5;
}
int DamageEnchantment::getMinCost(int a2) {
    return MIN_COST[this->mDamageType] + LEVEL_COST[this->mDamageType] * (a2 - 1);
}
int DamageEnchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + LEVEL_COST_2[this->mDamageType];
}

// down here was enum but I don't even care about it now
float DamageEnchantment::getDamageBonus(int a2, MobType mobType) {
    if (this->mDamageType == 0) {
        float result, lhs = (float)a2 - 1.0f, rhs = 0.0f;
        __asm__ volatile("fmaxnm %s[result], %s[lhs], %s[rhs]"
                         : [result] "=w"(result)
                         : [lhs] "w"(lhs), [rhs] "w"(rhs));
        return result * 0.5f + 1.0f;
    } else if (this->mDamageType == 1 && mobType == 1) {  // enum here
        return (float)a2 * 2.5f;
    } else {
        if (this->mDamageType == 2 && mobType == 2) {  // enum here
            return (float)a2 * 2.5f;
        }
    }
    return 0.0f;
}
bool DamageEnchantment::checkCompatibility(Enchantment const* other) {
    return !dynamic_cast<const DamageEnchantment*>(other);
}
int DamageEnchantment::getDescriptionId() {
    return NAME_IDS[this->mDamageType];
}
bool DamageEnchantment::canEnchant(const not_null_ptr<ItemInstance>& instance) {
    return dynamic_cast<AxeItem*>(instance->getItem())
           || Enchantment::canEnchant(not_null_ptr<ItemInstance>(instance));
}
void DamageEnchantment::doPostAttack(const std::shared_ptr<LivingEntity>& a2,
                                     const std::shared_ptr<Entity>& a3, int a4) {
    if (a3->isType(eINSTANCEOF::eLivingEntity)) {
        std::shared_ptr<LivingEntity> livingEnt = std::static_pointer_cast<LivingEntity>(a3);
        if (this->mDamageType == 2 && livingEnt->getMobType() == 2) {
            int v14 = 20 + a2->getRandom()->nextInt(10 * a4);
            livingEnt->addEffect(new MobEffectInstance(MobEffects::SLOWNESS, v14, 3), nullptr);
        }
    }
}