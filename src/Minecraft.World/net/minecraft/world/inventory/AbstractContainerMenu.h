#pragma once

#include "net/minecraft/world/item/ItemInstance.h"
#include <cstdint>
#include <memory>

class net_minecraft_world_inventory {
public:
    class ContainerListener;
};
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
    virtual ~AbstractContainerMenu();
    virtual void addSlotListener(net_minecraft_world_inventory::ContainerListener*);
    virtual void removeSlotListener(net_minecraft_world_inventory::ContainerListener*);
    virtual void getItems();
    virtual void sendData(int, int);
    virtual void broadcastChanges();
    virtual void needsRendered();
    virtual void clickMenuButton(std::shared_ptr<Player>, int);
    virtual void getSlotFor(std::shared_ptr<Container>, int);
    virtual void getSlot(int);
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
    virtual void isValidIngredient(not_null_ptr<ItemInstance>, int);

    void* qword8;
    void* qword10;
    void* qword18;
    void* qword20;
    void* qword28;
    void* qword30;
    int dword38;
    uint16_t word3C;
    __attribute__((aligned(4))) void* qword40;
    void* qword48;
    void* qword50;
    void* qword58;
    void* qword60;
    int dword68;
    char gap6C[4];
    char byte70;
    char gap71[7];
    void* qword78;
    void* qword80;
    void* qword88;
    char byte90;
    __attribute__((aligned(4))) int dword94;
    void* qword98;
    void* qwordA0;
    void* qwordA8;
    void* qwordB0;
    int dwordB8;
    char gapBC[4];
    void* qwordC0;
    void* qwordC8;
    void* qwordD0;
    void* qwordD8;
    int dwordE0;
};
