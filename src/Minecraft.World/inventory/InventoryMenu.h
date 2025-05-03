#include "Minecraft.World/inventory/AbstractContainerMenu.h"
#include <memory>

class Player;
class Inventory;

class InventoryMenu : public AbstractContainerMenu {
public:
    InventoryMenu(std::shared_ptr<Inventory>, bool, Player*);

    void* qwordE8;
    void* qwordF0;
    void* qwordF8;
    void* qword100;
    void* qword108;
    void* qword110;
};