#pragma once

#include "net/minecraft/world/inventory/AbstractContainerMenu.h"
#include <memory>

class Player;
class Inventory;

class InventoryMenu : public AbstractContainerMenu {
public:
    InventoryMenu(std::shared_ptr<Inventory>, bool, Player*);

    // there is more overloads, but I'm not bothered to do it now
    ~InventoryMenu() override;
    void stillValid(std::shared_ptr<Player>) override;

    static void staticCtor();

    void* m_qwordE8;
    void* m_qwordF0;
    void* m_qwordF8;
    void* m_qword100;
    void* m_qword108;
    void* m_qword110;
};
