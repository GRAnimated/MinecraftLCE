#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/item/Rarity.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"
#include "net/minecraft/world/item/enchantment/EnchantmentCategory.h"

#include "net/minecraft/world/enchantment/categories/ArmorCategory.h"
#include "net/minecraft/world/enchantment/categories/BowCategory.h"
#include "net/minecraft/world/enchantment/categories/BreakableCategory.h"
#include "net/minecraft/world/enchantment/categories/ChestArmorCategory.h"
#include "net/minecraft/world/enchantment/categories/DiggerCategory.h"
#include "net/minecraft/world/enchantment/categories/FeetArmorCategory.h"
#include "net/minecraft/world/enchantment/categories/FishingRodCategory.h"
#include "net/minecraft/world/enchantment/categories/HeadArmorCategory.h"
#include "net/minecraft/world/enchantment/categories/WeaponCategory.h"
#include "net/minecraft/world/enchantment/categories/WearableCategory.h"

#include "net/minecraft/world/enchantment/enchantments/ArrowDamageEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ArrowFireEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ArrowInfiniteEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ArrowKnockbackEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/BindingCurseEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/DamageEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/DigDurabilityEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/DiggingEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/FireAspectEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/FishingSpeedEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/FrostWalkerEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/KnockbackEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/LootBonusEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/MendingEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/OxygenEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ProtectionEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/ThornsEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/UntouchingEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/VanishingCurseEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/WaterWalkerEnchantment.h"
#include "net/minecraft/world/enchantment/enchantments/WaterWorkerEnchantment.h"

Enchantment::Enchantment(const Rarity* rarity, const EnchantmentCategory* category,
                         arrayWithLength<const EquipmentSlot*> array)
    : mEnchantmentCategory(category) {
    this->mRarity = rarity;
    this->mSlots = array;
}

extern MappedRegistry<ResourceLocation, Enchantment*>* sEnchantmentRegistry;

// keep in mind that arguments passed into as pointers may be wrong, I've checked them through but still some
// missmatch could occur
void Enchantment::staticCtor() {
    arrayWithLength<const EquipmentSlot*> ARMOR_SLOTS(4, true);
    ARMOR_SLOTS[0] = EquipmentSlot::HEAD;
    ARMOR_SLOTS[1] = EquipmentSlot::CHEST;
    ARMOR_SLOTS[2] = EquipmentSlot::LEGS;
    ARMOR_SLOTS[3] = EquipmentSlot::FEET;

    arrayWithLength<const EquipmentSlot*> MAIN_HAND_SLOT(1, true);
    MAIN_HAND_SLOT[0] = EquipmentSlot::MAINHAND;

    arrayWithLength<const EquipmentSlot*> FEET_SLOT(1, true);
    FEET_SLOT[0] = EquipmentSlot::FEET;

    arrayWithLength<const EquipmentSlot*> ALL_SLOTS(6, true);
    ALL_SLOTS[0] = EquipmentSlot::MAINHAND;
    ALL_SLOTS[1] = EquipmentSlot::OFFHAND;
    ALL_SLOTS[2] = EquipmentSlot::FEET;
    ALL_SLOTS[3] = EquipmentSlot::LEGS;
    ALL_SLOTS[4] = EquipmentSlot::CHEST;
    ALL_SLOTS[5] = EquipmentSlot::HEAD;

    sEnchantmentRegistry->registerMapping(
        0, ResourceLocation(L"protection"),
        new ProtectionEnchantment(Rarity::COMMON, ProtectionEnchantment::Type::ALL, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(
        1, ResourceLocation(L"fire_protection"),
        new ProtectionEnchantment(Rarity::UNCOMMON, ProtectionEnchantment::Type::FIRE, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(
        2, ResourceLocation(L"feather_falling"),
        new ProtectionEnchantment(Rarity::UNCOMMON, ProtectionEnchantment::Type::FALL, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(
        3, ResourceLocation(L"blast_protection"),
        new ProtectionEnchantment(Rarity::RARE, ProtectionEnchantment::Type::EXPLOSION, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(
        4, ResourceLocation(L"projectile_protection"),
        new ProtectionEnchantment(Rarity::UNCOMMON, ProtectionEnchantment::Type::PROJECTILE, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(5, ResourceLocation(L"respiration"),
                                          new OxygenEnchantment(Rarity::RARE, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(6, ResourceLocation(L"aqua_affinity"),
                                          new WaterWorkerEnchantment(Rarity::RARE, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(7, ResourceLocation(L"thorns"),
                                          new ThornsEnchantment(Rarity::EPIC, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(8, ResourceLocation(L"depth_strider"),
                                          new WaterWalkerEnchantment(Rarity::RARE, ARMOR_SLOTS));

    sEnchantmentRegistry->registerMapping(9, ResourceLocation(L"frost_walker"),
                                          new FrostWalkerEnchantment(Rarity::RARE, FEET_SLOT));

    sEnchantmentRegistry->registerMapping(10, ResourceLocation(L"binding_curse"),
                                          new BindingCurseEnchantment(Rarity::EPIC, FEET_SLOT));

    sEnchantmentRegistry->registerMapping(16, ResourceLocation(L"sharpness"),
                                          new DamageEnchantment(Rarity::COMMON, 0, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(17, ResourceLocation(L"smite"),
                                          new DamageEnchantment(Rarity::UNCOMMON, 1, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(18, ResourceLocation(L"bane_of_arthropods"),
                                          new DamageEnchantment(Rarity::UNCOMMON, 2, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(19, ResourceLocation(L"knockback"),
                                          new KnockbackEnchantment(Rarity::UNCOMMON, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(20, ResourceLocation(L"fire_aspect"),
                                          new FireAspectEnchantment(Rarity::RARE, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(
        21, ResourceLocation(L"looting"),
        new LootBonusEnchantment(Rarity::RARE, WeaponCategory::sWeaponCategory, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(32, ResourceLocation(L"efficiency"),
                                          new DiggingEnchantment(Rarity::COMMON, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(33, ResourceLocation(L"silk_touch"),
                                          new UntouchingEnchantment(Rarity::EPIC, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(34, ResourceLocation(L"unbreaking"),
                                          new DigDurabilityEnchantment(Rarity::UNCOMMON, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(
        35, ResourceLocation(L"fortune"),
        new LootBonusEnchantment(Rarity::RARE, DiggerCategory::sDiggerCategory, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(48, ResourceLocation(L"power"),
                                          new ArrowDamageEnchantment(Rarity::COMMON, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(49, ResourceLocation(L"punch"),
                                          new ArrowKnockbackEnchantment(Rarity::UNCOMMON, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(50, ResourceLocation(L"flame"),
                                          new ArrowFireEnchantment(Rarity::RARE, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(51, ResourceLocation(L"infinity"),
                                          new ArrowInfiniteEnchantment(Rarity::EPIC, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(
        61, ResourceLocation(L"luck_of_the_sea"),
        new LootBonusEnchantment(Rarity::RARE, FishingRodCategory::sFishingRodCategory, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(
        62, ResourceLocation(L"lure"),
        new FishingSpeedEnchantment(Rarity::RARE, FishingRodCategory::sFishingRodCategory, MAIN_HAND_SLOT));

    sEnchantmentRegistry->registerMapping(70, ResourceLocation(L"mending"),
                                          new MendingEnchantment(Rarity::RARE, ALL_SLOTS));

    sEnchantmentRegistry->registerMapping(71, ResourceLocation(L"vanishing_curse"),
                                          new VanishingCurseEnchantment(Rarity::EPIC, ALL_SLOTS));
}

const Rarity* Enchantment::getRarity() {
    return this->mRarity;
}

void Enchantment::getSlotItems(const std::shared_ptr<LivingEntity>&) {}

int Enchantment::getMinLevel() {
    return 1;
}

int Enchantment::getMaxLevel() {
    return 1;
}

int Enchantment::getMinCost(int a2) {
    return (10 * a2) | 1;
}

int Enchantment::getMaxCost(int a2) {
    return this->getMinCost(a2) + 5;
}

int Enchantment::getDamageProtection(int, const DamageSource*) {
    return 0;
}

float Enchantment::getDamageBonus(int, MobType) {
    return 0.0f;
}

bool Enchantment::checkCompatibility(const Enchantment* a2) {
    return this != a2;
}

void Enchantment::setDescriptionId(int a2) {
    this->mDescriptionId = a2;
}

int Enchantment::getDescriptionId() {
    return this->mDescriptionId;
}

bool Enchantment::canEnchant(const not_null_ptr<ItemInstance>& item) {
    return this->mEnchantmentCategory->canEnchant(item->getItem());
}

void Enchantment::doPostAttack(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) {}

void Enchantment::doPostHurt(const std::shared_ptr<LivingEntity>&, const std::shared_ptr<Entity>&, int) {}

bool Enchantment::isTreasureOnly() {
    return false;
}

bool Enchantment::isCurse() {
    return false;
}

// I don't know how to handle destructors...
Enchantment::~Enchantment() {}