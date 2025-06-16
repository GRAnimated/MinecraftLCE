#include "Minecraft.World/item/DiggerItem.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Block.h"

DiggerItem::DiggerItem(Item::Tier const* tier, arrayWithLength<Block*> blocks) : mTier(tier) {
    this->_init(0, 0, blocks);
}

DiggerItem::DiggerItem(float attackDamage, float attackSpeed, Item::Tier const* tier,
                       arrayWithLength<Block*> blocks)
    : mTier(tier) {
    this->_init(attackDamage, attackSpeed, blocks);
}

void DiggerItem::_init(float attackDamage, float attackSpeed, arrayWithLength<Block*> blocks) {
    this->mBlocks = blocks;
    this->mMaxStackSize = 1;
    this->setMaxDamage(this->mTier->getUses());
    this->mSpeed = this->mTier->getSpeed();
    this->mAttackDamage = this->mTier->getAttackDamageBonus() + attackDamage;
    this->mAttackSpeed = attackSpeed;
}

DiggerItem::~DiggerItem() {}

float DiggerItem::getDestroySpeed(not_null_ptr<ItemInstance> item, BlockState* state) {
    for (int i = 0; i < this->mBlocks.length; i++) {
        if (this->mBlocks[i] == state->getBlock()) {
            return this->mSpeed;
        }
    }
    return 1.0f;
}

bool DiggerItem::hurtEnemy(not_null_ptr<ItemInstance> item, std::shared_ptr<LivingEntity> attacker,
                           std::shared_ptr<LivingEntity> victim) {
    item->hurtAndBreak(2, victim);
    return true;
}

bool DiggerItem::mineBlock(not_null_ptr<ItemInstance> item, Level* level, const BlockState* state,
                           const BlockPos& pos, std::shared_ptr<LivingEntity> user) {
    if (!level->mIsLocal && state->getDestroySpeed(level, pos) != 0.0f) {
        item->hurtAndBreak(1, user);
    }
    return true;
}

bool DiggerItem::isHandEquipped() {
    return true;
}

int DiggerItem::getEnchantmentValue() {
    return this->mTier->getEnchantmentValue();
}

bool DiggerItem::isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem) {
    return this->mTier->getTierItem() == repairItem->getItem() || Item::isValidRepairItem(source, repairItem);
}

// TODO: maybe not today, implement it later, after REing AttributeModifier
// void DiggerItem::getDefaultAttributeModifiers(const EquipmentSlot*) {}