#include "net/minecraft/world/item/ItemBootstrapTypes.h"
#include "net/minecraft/world/item/LeadItem.h"

// Recovered catalogue dependencies. Derived virtual behavior and destructors
// remain separate reconstruction work, so their vtables are external symbols.
BoatItem::BoatItem(int type) : m_type(type) {
    m_maxStackSize = 1;
}

BookItem::BookItem() {}

BowlFoodItem::BowlFoodItem(int nutrition) : FoodItem(nutrition, false) {
    setMaxStackSize(1);
}

BucketItem::BucketItem(Block* block) : m_block(block) {
    m_maxStackSize = 1;
}

DoorItem::DoorItem(Block* block) : m_block(block) {}

EggItem::EggItem() {
    m_maxStackSize = 16;
}

FlintAndSteelItem::FlintAndSteelItem() {
    m_maxStackSize = 1;
    setMaxDamage(64);
}

LeadItem::LeadItem() {}

MilkBucketItem::MilkBucketItem() {
    setMaxStackSize(1);
}

SaddleItem::SaddleItem() {
    m_maxStackSize = 1;
}

SeedItem::SeedItem(Block* crop, Block* farmland) : m_crop(crop), m_farmland(farmland) {}

SnowballItem::SnowballItem() {
    m_maxStackSize = 16;
}

WritableBookItem::WritableBookItem() {
    setMaxStackSize(1);
}

WrittenBookItem::WrittenBookItem() {
    setMaxStackSize(1);
}
