#pragma once

#include "net/minecraft/world/item/ItemInstance.h"
#include "types.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace net_minecraft_world_inventory {
class ContainerListener;
};  // namespace net_minecraft_world_inventory
class Player;
class Container;
class ItemInstance;
class ClickType {
public:
    enum eClickType {};
};
class Slot;

class AbstractContainerMenu {
public:
    not_null_ptr<ItemInstance> GetQuickCraftItem(int, int);

    virtual ~AbstractContainerMenu();
    virtual void addSlotListener(net_minecraft_world_inventory::ContainerListener*);
    virtual void removeSlotListener(net_minecraft_world_inventory::ContainerListener*);
    virtual void getItems();
    virtual void sendData(int, int);
    virtual void broadcastChanges();
    virtual void needsRendered();
    virtual void clickMenuButton(std::shared_ptr<Player>, int);
    virtual Slot* getSlotFor(std::shared_ptr<Container>, int);
    virtual Slot* getSlot(int);
    virtual void getAllItems(int, int);
    virtual void takeAll(std::shared_ptr<Player>, int, int, int);
    virtual void quickMoveStack(std::shared_ptr<Player>, int);
    virtual void clicked(int, int, ClickType::eClickType, std::shared_ptr<Player>);
    virtual void mayCombine(Slot*, not_null_ptr<ItemInstance>);
    virtual void canTakeItemForPickAll(not_null_ptr<ItemInstance>, Slot*);
    virtual void doQuickMoveLoop();
    virtual void clearContainer(std::shared_ptr<Player>, Level*, std::shared_ptr<Container>);
    virtual void removed(std::shared_ptr<Player>);
    virtual void slotsChanged();
    virtual void setData(int, int);
    virtual void stillValid(std::shared_ptr<Player>) = 0;
    virtual void isOverrideResultClick(int, int);
    virtual bool isValidIngredient(not_null_ptr<ItemInstance>, int);

    int getSlotsCount() { return this->m_slots.size(); }

    std::vector<not_null_ptr<ItemInstance>> m_items;
    std::vector<Slot*> m_slots;
    int m_someValue;
    uint16_t m_word3C;
    __attribute__((aligned(4))) void* m_qword40;
    void* m_qword48;
    void* m_qword50;
    void* m_qword58;
    void* m_qword60;
    int m_dword68;
    char m_gap6C[4];
    char m_byte70;
    char m_gap71[7];
    void* m_qword78;
    void* m_qword80;
    void* m_qword88;
    char m_byte90;
    __attribute__((aligned(4))) int m_dword94;
    void* m_qword98;
    void* m_qwordA0;
    void* m_qwordA8;
    void* m_qwordB0;
    int m_dwordB8;
    char m_gapBc[4];
    void* m_qwordC0;
    void* m_qwordC8;
    void* m_qwordD0;
    void* m_qwordD8;
    int m_dwordE0;
};
