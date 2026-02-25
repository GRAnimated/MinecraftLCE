#include "net/minecraft/world/inventory/Slot.h"

#include "types.h"

#include "net/minecraft/world/Container.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"

Slot::Slot(std::shared_ptr<Container> container, int index, int x, int y)
    : m_slot(index), m_container(container), m_x(x), m_y(y) {}

Slot::~Slot() {}

void Slot::onQuickCraft(not_null_ptr<ItemInstance> item, not_null_ptr<ItemInstance> item2) {
    int count = item2->getCount() - item->getCount();
    if (count > 0) {
        onQuickCraft(item2, count);
    }
}

void Slot::onQuickCraft(not_null_ptr<ItemInstance> item, int count) {}

void Slot::onSwapCraft(int count) {}

void Slot::checkTakeAchievements(not_null_ptr<ItemInstance> item) {}

not_null_ptr<ItemInstance> Slot::onTake(std::shared_ptr<Player> player, not_null_ptr<ItemInstance> item) {
    setChanged();
    return item;
}

bool Slot::mayPlace(not_null_ptr<ItemInstance> item) {
    return true;
}

not_null_ptr<ItemInstance> Slot::getItem() {
    return m_container->getItem(m_slot);
}

bool Slot::hasItem() {
    return !getItem()->isEmpty();
}

void Slot::set(not_null_ptr<ItemInstance> item) {
    m_container->setItem(m_slot, item);
    setChanged();
}

void Slot::setChanged() {
    m_container->setChanged();
}

int Slot::getMaxStackSize() {
    return m_container->getMaxStackSize();
}

int Slot::getMaxStackSize(not_null_ptr<ItemInstance> item) {
    return getMaxStackSize();
}

std::wstring Slot::getNoItemIcon() {
    return nullptr;
}

not_null_ptr<ItemInstance> Slot::remove(int count) {
    return m_container->removeItem(m_slot, count);
}

bool Slot::isAt(std::shared_ptr<Container> container, int index) {
    return container.get() == m_container.get() && m_slot == index;
}

bool Slot::mayPickup(std::shared_ptr<Player> player) {
    return true;
}

bool Slot::isActive() {
    return true;
}

bool Slot::mayCombine(not_null_ptr<ItemInstance> item) {
    not_null_ptr<ItemInstance> thisItem = getItem();

    if (thisItem->isEmpty() || item->isEmpty() || thisItem->isEmpty() || item->isEmpty()) {
        return false;
    }
    if (thisItem->getItem()->getId() != item->getItem()->getId()) {
        return false;
    }
    if (thisItem->getCount() != 1 || item->getCount() != 1) {
        return false;
    }
    if (!thisItem->getItem()->canBeDepleted()) {
        return false;
    }
    if (!thisItem->isDamaged() && !item->isDamaged()) {
        return false;
    }
    if (thisItem->isEnchanted() || item->isEnchanted()) {
        return false;
    }

    return true;
}

// void Slot::combine(not_null_ptr<ItemInstance> item) {}
