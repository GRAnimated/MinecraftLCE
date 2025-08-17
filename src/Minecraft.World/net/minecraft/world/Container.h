#pragma once

#include "net/minecraft/world/Nameable.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "types.h"
#include <memory>

class Slot;
class ItemInstance;

class Container : public Nameable {
public:
    virtual ~Container();
    virtual void getContainerSize() = 0;
    virtual void isEmpty() = 0;
    virtual not_null_ptr<ItemInstance> getItem(unsigned int) = 0;
    virtual not_null_ptr<ItemInstance> removeItem(unsigned int, int) = 0;
    virtual void removeItemNoUpdate(int) = 0;
    virtual void setItem(unsigned int, not_null_ptr<ItemInstance>) = 0;
    virtual int getMaxStackSize() = 0;
    virtual void setChanged() = 0;
    virtual void stillValid(std::shared_ptr<Player>) = 0;
    virtual void startOpen(std::shared_ptr<Player>) = 0;
    virtual void stopOpen(std::shared_ptr<Player>) = 0;
    virtual void canPlaceItem(int, not_null_ptr<ItemInstance>) = 0;
    virtual void getContainerData(int) = 0;
    virtual void setContainerData(int, int) = 0;
    virtual void getContainerDataCount() = 0;
    virtual void clearContent() = 0;
};
