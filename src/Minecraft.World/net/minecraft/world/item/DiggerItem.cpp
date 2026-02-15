#include "net/minecraft/world/item/DiggerItem.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/entity/ai/attributes/Attribute.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

DiggerItem::DiggerItem(const Item::Tier* tier, arrayWithLength<Block*> blocks) : m_tier(tier) {
    this->_init(0, 0, blocks);
}

DiggerItem::DiggerItem(float attackDamage, float attackSpeed, const Item::Tier* tier,
                       arrayWithLength<Block*> blocks)
    : m_tier(tier) {
    this->_init(attackDamage, attackSpeed, blocks);
}

void DiggerItem::_init(float attackDamage, float attackSpeed, arrayWithLength<Block*> blocks) {
    this->m_blocks = blocks;
    this->m_maxStackSize = 1;
    this->setMaxDamage(this->m_tier->getUses());
    this->m_speed = this->m_tier->getSpeed();
    this->m_attackDamage = this->m_tier->getAttackDamageBonus() + attackDamage;
    this->m_attackSpeed = attackSpeed;
}

float DiggerItem::getDestroySpeed(not_null_ptr<ItemInstance> item, BlockState* state) {
    for (int i = 0; i < this->m_blocks.m_length; i++) {
        if (this->m_blocks[i] == state->getBlock()) {
            return this->m_speed;
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
    if (!level->m_isLocal && state->getDestroySpeed(level, pos) != 0.0f) {
        item->hurtAndBreak(1, user);
    }
    return true;
}

bool DiggerItem::isHandEquipped() {
    return true;
}

int DiggerItem::getEnchantmentValue() {
    return this->m_tier->getEnchantmentValue();
}

bool DiggerItem::isValidRepairItem(not_null_ptr<ItemInstance> source, not_null_ptr<ItemInstance> repairItem) {
    return this->m_tier->getTierItem() == repairItem->getItem()
           || Item::isValidRepairItem(source, repairItem);
}

std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>*
DiggerItem::getDefaultAttributeModifiers(const EquipmentSlot* eqpSlot) {
    std::unordered_map<eATTRIBUTE_ID, AttributeModifier*>* map = Item::getDefaultAttributeModifiers(eqpSlot);

    // that's very ugly, but couldn't match it any other way
    double v6 = this->m_attackDamage;
    v6 = Minecraft::InMiniGame(NORMAL_WORLD, true) ?
             Minecraft::GetInstance()->GetMiniGame()->getBaseDamage(this->getId(), this->m_attackDamage) :
             v6;
    //

    if (eqpSlot == EquipmentSlot::MAINHAND) {
        (*map)[(eATTRIBUTE_ID)RangedAttribute::ATTACK_DAMAGE->getId()]
            = new AttributeModifier(BASE_ATTACK_DAMAGE, v6, 0);

        (*map)[(eATTRIBUTE_ID)RangedAttribute::ATTACK_SPEED->getId()]
            = new AttributeModifier(BASE_ATTACK_SPEED, this->m_attackSpeed, 0);
    }
    return map;
}
