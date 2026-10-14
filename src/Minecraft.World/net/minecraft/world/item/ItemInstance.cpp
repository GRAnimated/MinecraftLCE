#include "net/minecraft/world/item/ItemInstance.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/CensoredString.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"

#include <algorithm>

void ItemInstance::init(Item* item, int count, int aux) {
    m_count = count;
    m_dword14 = 0;
    m_damage = aux;
    m_item = item;
    m_tag = nullptr;
    m_byte30 = false;
    m_censoredString = std::shared_ptr<CensoredString>(
        new CensoredString(StringIDs::AwaitingApproval, StringIDs::Censored));
    m_qword58 = nullptr;
    m_byte60 = false;
    updateEmptyCacheFlag();
}

ItemInstance::~ItemInstance() {
    if (m_tag)
        delete m_tag;
}

ItemInstance::ItemInstance(Block* block) {
    this->init(Item::byBlock(block), 1, 0);
}

ItemInstance::ItemInstance(Block* block, int count) {
    this->init(Item::byBlock(block), count, block->convertBlockStateToLegacyData(block->defaultBlockState()));
}

ItemInstance::ItemInstance(Block* block, int count, int aux) {
    this->init(Item::byBlock(block), count, aux);
}

ItemInstance::ItemInstance(Item* item) {
    this->init(item, 1, 0);
}

ItemInstance::ItemInstance(Item* item, int count) {
    this->init(item, count, 0);
}

ItemInstance::ItemInstance(Item* item, int count, int aux) {
    this->init(item, count, aux);
}

ItemInstance::ItemInstance(CompoundTag* compoundTag) {
    this->init(nullptr, 0, 0);
    this->m_item = Item::byString(compoundTag->getString(L"id"));
    this->m_dword14 = 0;
    this->m_count = compoundTag->getByte(L"Count");
    this->m_damage = compoundTag->getShort(L"Damage");

    if ((this->m_damage & 0x80000000) != 0)
        this->m_damage = 0;

    if (compoundTag->contains(L"tag", 10)) {
        if (this->m_tag)
            delete this->m_tag;

        this->m_tag = compoundTag->getCompound(L"tag")->copy();

        if (this->m_item)
            this->m_item->verifyTagAfterLoad(this->m_tag);
    }
    this->updateEmptyCacheFlag();
}

CompoundTag* ItemInstance::save(CompoundTag* tag) {
    ResourceLocation key = Items::Registry.getKey(m_item);
    tag->putString(L"id", key.toString());
    tag->putByte(L"Count", m_count);
    tag->putShort(L"Damage", m_damage);
    if (m_tag)
        tag->put(L"tag", m_tag->copy());
    return tag;
}

bool ItemInstance::isEmpty() const {
    return this == EMPTY.get() || m_item == nullptr || m_item == Item::byBlock(Blocks::AIR) || m_count < 1;
}

void ItemInstance::updateEmptyCacheFlag() {
    m_isEmpty = isEmpty();
}

Item* ItemInstance::getItem() const {
    return m_isEmpty ? Item::byBlock(Blocks::AIR) : m_item;
}

int ItemInstance::getCount() {
    return m_isEmpty ? 0 : m_count;
}

void ItemInstance::setCount(int count) {
    m_count = count;
    updateEmptyCacheFlag();
}

void ItemInstance::grow(int count) {
    setCount(m_count + count);
}

void ItemInstance::shrink(int count) {
    grow(-count);
}

int ItemInstance::getMaxStackSize() {
    return getItem()->getMaxStackSize();
}

bool ItemInstance::isStackable() {
    return getMaxStackSize() > 1 && (!isDamageableItem() || !isDamaged());
}

bool ItemInstance::isStackedByData() {
    return getItem()->isStackedByData();
}

bool ItemInstance::isDamaged() {
    return isDamageableItem() && m_damage > 0;
}

bool ItemInstance::isDamageableItem() {
    return !m_isEmpty && m_item->getMaxDamage() > 0 && (!hasTag() || !getTag()->getBoolean(L"Unbreakable"));
}

int ItemInstance::getDamageValue() {
    return m_damage;
}

int ItemInstance::getAuxValue() const {
    return m_damage;
}

bool ItemInstance::hasTag() {
    return !m_isEmpty && m_tag != nullptr;
}

CompoundTag* ItemInstance::getTag() {
    return m_tag;
}

void ItemInstance::setTag(CompoundTag* tag) {
    if (m_tag)
        delete m_tag;
    m_tag = tag;
}

bool ItemInstance::tagMatches(const not_null_ptr<ItemInstance>& first,
                              const not_null_ptr<ItemInstance>& second) {
    if (first->isEmpty() && second->isEmpty())
        return true;
    if (first->isEmpty() || second->isEmpty())
        return false;
    return first->m_tag ? first->m_tag->equals(second->m_tag) : second->m_tag == nullptr;
}

not_null_ptr<ItemInstance> ItemInstance::copy() const {
    not_null_ptr<ItemInstance> result(new ItemInstance(m_item, m_count, m_damage));
    if (m_tag)
        result->m_tag = m_tag->copy();
    return result;
}

not_null_ptr<ItemInstance> ItemInstance::split(int count) {
    int amount = std::min(count, m_count);
    auto result = copy();
    result->setCount(amount);
    shrink(amount);
    if (m_count < 1)
        m_count = 0;
    return result;
}

void ItemInstance::setPopTime(int ticks) {
    m_dword14 = ticks;
}
