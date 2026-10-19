#include "net/minecraft/world/inventory/Inventory.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/ListTag.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/level/gamemode/GameMode.h"
#include "net/minecraft/world/phys/AABB.h"

#include <algorithm>

Inventory::Inventory(Player* player) : m_lastSelected(ItemInstance::EMPTY), m_carried(ItemInstance::EMPTY) {
    m_items = NonNullList<not_null_ptr<ItemInstance>>::withSize(36, ItemInstance::EMPTY);
    m_armor = NonNullList<not_null_ptr<ItemInstance>>::withSize(4, ItemInstance::EMPTY);
    m_offhand = NonNullList<not_null_ptr<ItemInstance>>::withSize(1, ItemInstance::EMPTY);
    m_itemsView = m_items;
    m_armorView = m_armor;
    m_offhandView = m_offhand;
    m_selected = 0;
    m_selectionChanged = false;
    m_carried = ItemInstance::EMPTY;
    m_timesChanged = 0;
    m_player = player;
}

// NON_MATCHING | score: 4320 (lower is better)
Inventory::~Inventory() {
    m_items.deleteData();
    m_armor.deleteData();
    m_offhand.deleteData();
}

// name guessed
const not_null_ptr<ItemInstance>& Inventory::getSelected() {
    return isHotbarSlot(m_selected) ? m_items[m_selected] : ItemInstance::EMPTY;
}

// name guessed
// NON_MATCHING | score: 315 (lower is better)
bool Inventory::isHotbarSlot(int slot) {
    return slot >= 0 && slot < 9;
}

// name guessed
int Inventory::getSelectionSize() {
    return 9;
}

void Inventory::swapPaint(int direction) {
    if (direction > 0)
        direction = 1;
    if (direction < 0)
        direction = -1;
    m_selected -= direction;
    while (m_selected < 0)
        m_selected += 9;
    while (m_selected >= 9)
        m_selected -= 9;
}

/** Nonmatching: minigame-specific slot restrictions remain to be reconstructed.
 */
// name guessed
// NON_MATCHING | score: 1995 (lower is better)
int Inventory::getFreeSlot() {
    for (unsigned int i = 0; i < m_items.size(); ++i) {
        if (m_items[i]->isEmpty())
            return i;
    }
    return -1;
}

// name guessed
bool Inventory::isSameItem(not_null_ptr<ItemInstance> first, not_null_ptr<ItemInstance> second,
                           bool ignoreTags) {
    return first->getItem() == second->getItem()
           && (!first->isStackedByData() || first->getAuxValue() == second->getAuxValue())
           && (ignoreTags || ItemInstance::tagMatches(first, second));
}

// name guessed
// NON_MATCHING | score: 315 (lower is better)
bool Inventory::hasRemainingSpaceForItem(not_null_ptr<ItemInstance> slot, not_null_ptr<ItemInstance> item,
                                         bool ignoreTags) {
    return !slot->isEmpty() && isSameItem(slot, item, ignoreTags) && slot->isStackable()
           && slot->getCount() < slot->getMaxStackSize() && slot->getCount() < getMaxStackSize();
}

// name guessed
int Inventory::getSlotWithRemainingSpace(not_null_ptr<ItemInstance> item) {
    if (hasRemainingSpaceForItem(getItem(m_selected), item, false))
        return m_selected;
    if (hasRemainingSpaceForItem(getItem(40), item, false))
        return 40;
    for (int i = 0; i < static_cast<int>(m_items.size()); ++i) {
        if (hasRemainingSpaceForItem(m_items[i], item, false))
            return i;
    }
    return -1;
}

// name guessed
int Inventory::addResource(not_null_ptr<ItemInstance> item) {
    if (GameMode* mode = m_player->GetGameMode())
        mode->RecordItem(item);
    int slot = getSlotWithRemainingSpace(item);
    if (slot == -1)
        slot = getFreeSlot();
    if (slot == -1)
        return item->getCount();
    return addResource(slot, item);
}

// name guessed
// NON_MATCHING | score: 7969 (lower is better)
int Inventory::addResource(int slot, not_null_ptr<ItemInstance> item) {
    if (slot < 0 || slot >= getContainerSize())
        return item->getCount();
    Item* type = item->getItem();
    int remaining = item->getCount();
    auto stack = getItem(slot);
    if (!stack->isEmpty() && !isSameItem(stack, item, false))
        return remaining;
    if (stack->isEmpty()) {
        stack = not_null_ptr<ItemInstance>(new ItemInstance(type, 0, item->getAuxValue()));
        if (item->hasTag()) {
            stack->setTag(item->getTag()->copy());
            m_player->handleCollectItem(item);
        }
        setItem(slot, stack);
    }
    // A newly created zero-count stack reports AIR through getItem(). Use the
    // incoming item's limit until the destination becomes nonempty.
    int amount = std::min(remaining, item->getMaxStackSize() - stack->getCount());
    amount = std::min(amount, getMaxStackSize() - stack->getCount());
    if (amount > 0) {
        remaining -= amount;
        stack->grow(amount);
        stack->setPopTime(5);
    }
    return remaining;
}

bool Inventory::add(not_null_ptr<ItemInstance> item) {
    return add(-1, item);
}

/** Nonmatching: item-collection statistics and achievements remain to be reconstructed.
 */
// name guessed
// NON_MATCHING | score: 15193 (lower is better)
bool Inventory::add(int slot, not_null_ptr<ItemInstance> item) {
    if (item->isEmpty() || slot < -1 || slot >= getContainerSize())
        return false;
    if (item->isDamaged()) {
        if (slot >= static_cast<int>(m_items.size()))
            return false;
        if (slot == -1)
            slot = getFreeSlot();
        if (slot >= 0) {
            m_player->handleCollectItem(item);
            m_items.set(slot, item->copy());
            m_items[slot]->setPopTime(5);
            item->setCount(0);
            return true;
        }
        if (m_player->m_abilities.m_isInstabuild) {
            item->setCount(0);
            return true;
        }
        return false;
    }
    int previous;
    do {
        previous = item->getCount();
        item->setCount(slot == -1 ? addResource(item) : addResource(slot, item));
    } while (!item->isEmpty() && item->getCount() < previous);
    if (item->getCount() == previous && m_player->m_abilities.m_isInstabuild) {
        item->setCount(0);
        return true;
    }
    return item->getCount() < previous;
}

bool Inventory::hasResource(Item* item) {
    for (unsigned int i = 0; i < m_items.size(); ++i) {
        if (!m_items[i]->isEmpty() && m_items[i]->getItem() == item)
            return true;
    }
    return false;
}

NonNullList<not_null_ptr<ItemInstance>> Inventory::getSlotList(unsigned int& index) {
    if (index < m_itemsView.size())
        return m_itemsView;
    index -= m_itemsView.size();
    if (index < m_armorView.size())
        return m_armorView;
    index -= m_armorView.size();
    if (index < m_offhandView.size())
        return m_offhandView;
    return {};
}

// name guessed
int Inventory::getContainerSize() {
    return m_items.size() + m_armor.size() + m_offhand.size();
}

// name guessed
// NON_MATCHING | score: 7826 (lower is better)
bool Inventory::isEmpty() {
    for (auto list : {m_items, m_armor, m_offhand}) {
        for (unsigned int i = 0; i < list.size(); ++i) {
            auto item = list[i];
            if (!item->isEmpty())
                return false;
        }
    }
    return true;
}

// name guessed
// NON_MATCHING | score: 3924 (lower is better)
not_null_ptr<ItemInstance> Inventory::getItem(unsigned int index) {
    auto list = getSlotList(index);
    return list.size() == 0 ? ItemInstance::EMPTY : list[index];
}

// name guessed
// NON_MATCHING | score: 4222 (lower is better)
not_null_ptr<ItemInstance> Inventory::removeItem(unsigned int index, int count) {
    auto list = getSlotList(index);
    if (list.size() == 0 || count <= 0 || list[index]->isEmpty())
        return ItemInstance::EMPTY;
    auto result = list[index]->split(count);
    if (list[index]->isEmpty())
        list.set(index, ItemInstance::EMPTY);
    return result;
}

// name guessed
// NON_MATCHING | score: 4526 (lower is better)
not_null_ptr<ItemInstance> Inventory::removeItemNoUpdate(int slot) {
    unsigned int index = slot;
    auto list = getSlotList(index);
    if (list.size() == 0 || list[index]->isEmpty())
        return ItemInstance::EMPTY;
    auto item = list[index];
    list.set(index, ItemInstance::EMPTY);
    return item;
}

// NON_MATCHING | score: 5905 (lower is better)
void Inventory::removeItem(not_null_ptr<ItemInstance> item) {
    for (auto list : {m_itemsView, m_armorView, m_offhandView}) {
        for (unsigned int i = 0; i < list.size(); ++i) {
            if (list[i] == item) {
                list.set(i, ItemInstance::EMPTY);
                break;
            }
        }
    }
}

// name guessed
// NON_MATCHING | score: 6252 (lower is better)
void Inventory::setItem(unsigned int index, not_null_ptr<ItemInstance> item) {
    bool empty = item->isEmpty();
    unsigned int slot = index;
    auto list = getSlotList(slot);
    if (list.size() == 0)
        return;
    if (index >= m_itemsView.size() && index < m_itemsView.size() + m_armorView.size() && !empty
        && m_player->isType(eLocalPlayer))
        m_player->OnEquipArmor(item);
    list.set(slot, item);
    m_player->handleCollectItem(item);
}

// name guessed
int Inventory::getMaxStackSize() {
    return 64;
}

// name guessed
void Inventory::setChanged() {
    ++m_timesChanged;
}

// name guessed
not_null_ptr<ItemInstance> Inventory::getArmor(int index) {
    return m_armor[index];
}

// name guessed
void Inventory::setCarried(not_null_ptr<ItemInstance> item) {
    m_carried = item;
    m_player->handleCollectItem(item);
}

not_null_ptr<ItemInstance> Inventory::getCarried() {
    return m_carried;
}

// name guessed
ListTag* Inventory::save(ListTag* tags) {
    for (unsigned int i = 0; i < m_items.size(); ++i) {
        if (!m_items[i]->isEmpty()) {
            auto tag = new CompoundTag();
            tag->putByte(L"Slot", i);
            m_items[i]->save(tag);
            tags->add(tag);
        }
    }
    for (unsigned int i = 0; i < m_armor.size(); ++i) {
        if (!m_armor[i]->isEmpty()) {
            auto tag = new CompoundTag();
            tag->putByte(L"Slot", i + 100);
            m_armor[i]->save(tag);
            tags->add(tag);
        }
    }
    for (unsigned int i = 0; i < m_offhand.size(); ++i) {
        if (!m_offhand[i]->isEmpty()) {
            auto tag = new CompoundTag();
            tag->putByte(L"Slot", i + 150);
            m_offhand[i]->save(tag);
            tags->add(tag);
        }
    }
    return tags;
}

void Inventory::load(ListTag* tags) {
    m_items.clear();
    m_armor.clear();
    m_offhand.clear();
    for (int i = 0; i < static_cast<int>(tags->size()); ++i) {
        CompoundTag* tag = tags->getCompound(i);
        unsigned int slot = tag->getByte(L"Slot") & 0xff;
        not_null_ptr<ItemInstance> item(new ItemInstance(tag));
        if (item->isEmpty())
            continue;
        if (slot < m_items.size())
            m_items.set(slot, item);
        else if (slot >= 100 && slot < m_armor.size() + 100)
            m_armor.set(slot - 100, item);
        else if (slot >= 150 && slot < m_offhand.size() + 150)
            m_offhand.set(slot - 150, item);
    }
}

// name guessed
std::wstring Inventory::getName() {
    return L10N::GetString(StringIDs::Inventory_2);
}

// name guessed
std::wstring Inventory::getCustomName() {
    return L"";
}

// name guessed
bool Inventory::hasCustomName() {
    return false;
}

// name guessed
std::wstring Inventory::getDisplayName() {
    return hasCustomName() ? getCustomName() : getName();
}

// name guessed
// NON_MATCHING | score: 3771 (lower is better)
bool Inventory::stillValid(std::shared_ptr<Player> player) {
    if (m_player->m_isRemoved)
        return false;
    BlockPos pos(m_player->getPos(1.0f));
    const AABB* box = player->getBoundingBox();
    Vec3* center = Vec3::newTemp(pos.getX() + 0.5, pos.getY() + 0.5, pos.getZ() + 0.5);
    double radius = (box->m_axX - box->m_inX) * 0.5 + 1.8 + (box->m_axY - box->m_inY) * 0.5;
    return center->distanceToSqr(box->getCenter()) - radius * radius <= 30.25;
}

// name guessed
void Inventory::startOpen(std::shared_ptr<Player>) {}

// name guessed
void Inventory::stopOpen(std::shared_ptr<Player>) {}

// name guessed
bool Inventory::canPlaceItem(int, not_null_ptr<ItemInstance>) {
    return true;
}

// name guessed
int Inventory::getContainerData(int) {
    return 0;
}

// name guessed
void Inventory::setContainerData(int, int) {}

// name guessed
int Inventory::getContainerDataCount() {
    return 0;
}

// name guessed
void Inventory::clearContent() {
    m_itemsView.clear();
    m_armorView.clear();
    m_offhandView.clear();
}
