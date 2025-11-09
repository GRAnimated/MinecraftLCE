#pragma once

#include "net/minecraft/world/Container.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "types.h"

class Inventory : public Container {
public:
    bool add(not_null_ptr<ItemInstance>);
    bool hasResource(Item*);
    not_null_ptr<ItemInstance> getCarried();

    void getName() override;
    void getCustomName() override;
    void hasCustomName() override;
    void getDisplayName() override;
    ~Inventory();
    void getContainerSize() override;
    void isEmpty() override;
    not_null_ptr<ItemInstance> getItem(unsigned int) override;
    not_null_ptr<ItemInstance> removeItem(unsigned int, int) override;
    void removeItemNoUpdate(int) override;
    void setItem(unsigned int, not_null_ptr<ItemInstance>) override;
    int getMaxStackSize() override;
    void setChanged() override;
    void stillValid(std::shared_ptr<Player>) override;
    void startOpen(std::shared_ptr<Player>) override;
    void stopOpen(std::shared_ptr<Player>) override;
    void canPlaceItem(int, not_null_ptr<ItemInstance>) override;
    void getContainerData(int) override;
    void setContainerData(int, int) override;
    void getContainerDataCount() override;
    void clearContent() override;
};
