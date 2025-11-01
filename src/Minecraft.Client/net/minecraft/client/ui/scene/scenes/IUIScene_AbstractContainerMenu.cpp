#include "net/minecraft/client/ui/scene/scenes/IUIScene_AbstractContainerMenu.h"
#include "net/minecraft/world/item/ItemInstance.h"

bool IUIScene_AbstractContainerMenu::IsSameItemAs(not_null_ptr<ItemInstance> a,
                                                  not_null_ptr<ItemInstance> b) {
    if (a->isEmpty() || b->isEmpty())
        return false;

    if (a->getItem() != b->getItem())
        return false;

    if (b->isStackedByData() && b->getAuxValue() != a->getAuxValue())
        return false;

    return ItemInstance::tagMatches(b, a);
}
