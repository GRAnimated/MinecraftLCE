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

    void* qwordE8;
    void* qwordF0;
    void* qwordF8;
    void* qword100;
    void* qword108;
    void* qword110;
};
