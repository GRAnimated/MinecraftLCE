#include "net/minecraft/world/item/ItemBootstrapTypes.h"

BlockPlanterItem::BlockPlanterItem(Block* block) : m_block(block) {}

BottleItem::BottleItem() {}

CarrotOnAStickItem::CarrotOnAStickItem() {
    setMaxStackSize(1);
    setMaxDamage(25);
}

EnchantedBookItem::EnchantedBookItem() {}

EnderEyeItem::EnderEyeItem() {}

EnderpearlItem::EnderpearlItem() {
    m_maxStackSize = 16;
}

ExperienceBottleItem::ExperienceBottleItem() {}

FireworksItem::FireworksItem() {}

HangingEntityItem::HangingEntityItem(eINSTANCEOF type) : m_type(type) {}

NameTagItem::NameTagItem() {}

RedStoneDustItem::RedStoneDustItem() {}

SignItem::SignItem() {
    m_maxStackSize = 16;
}

SimpleFoiledItem::SimpleFoiledItem() {}
