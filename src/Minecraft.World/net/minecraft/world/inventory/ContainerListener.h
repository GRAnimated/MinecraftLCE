#pragma once

#include "types.h"
#include <memory>

class AbstractContainerMenu;
class Container;
class ItemInstance;

namespace net_minecraft_world_inventory {
class ContainerListener {
    ContainerListener();

    virtual ~ContainerListener() = default;
    virtual void refreshContainer(AbstractContainerMenu*, std::vector<not_null_ptr<ItemInstance>>*) = 0;
    virtual void slotChanged(AbstractContainerMenu*, int, not_null_ptr<ItemInstance>) = 0;
    virtual void setContainerData(AbstractContainerMenu*, int, int) = 0;
    virtual void setAllContainerData(AbstractContainerMenu*, std::shared_ptr<Container>) = 0;
};
}  // namespace net_minecraft_world_inventory
