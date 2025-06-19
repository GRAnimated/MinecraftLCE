#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.World/inventory/EquipmentSlot.h"
#include "Minecraft.World/item/Attribute.h"
#include "Minecraft.World/item/DiggerItem.h"
#include "Minecraft.World/item/Item.h"
#include "Minecraft.World/item/ItemInstance.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"

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

bool DiggerItem::hurtEnemy(not_null_ptr<ItemInstance> item, std::shared_ptr<LivingEntity> victim,
                           std::shared_ptr<LivingEntity> attacker) {
    item->hurtAndBreak(2, attacker);
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

std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>*
DiggerItem::getDefaultAttributeModifiers(const EquipmentSlot* eqpSlot) {
    std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>* map = Item::getDefaultAttributeModifiers(eqpSlot);

    // that's very ugly, but couldn't match it any other way
    double v6 = this->mAttackDamage;
    v6 = Minecraft::InMiniGame(NORMAL_WORLD, true) ?
             Minecraft::GetInstance()->GetMiniGame()->getBaseDamage(this->getId(), this->mAttackDamage) :
             v6;
    //

    if (eqpSlot == EquipmentSlot::MAINHAND) {
        (*map)[(eATTRIBUTE_ID)RangedAttribute::ATTACK_DAMAGE->getId()]
            = new AttributeModifier(BASE_ATTACK_DAMAGE, v6, 0);

        (*map)[(eATTRIBUTE_ID)RangedAttribute::ATTACK_SPEED->getId()]
            = new AttributeModifier(BASE_ATTACK_SPEED, this->mAttackSpeed, 0);
    }
    return map;
}