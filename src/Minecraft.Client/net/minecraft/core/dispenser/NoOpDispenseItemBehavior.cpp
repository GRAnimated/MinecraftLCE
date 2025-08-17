#include "net/minecraft/core/dispenser/NoOpDispenseItemBehavior.h"

not_null_ptr<ItemInstance> NoOpDispenseItemBehavior::dispense(BlockSource* source,
                                                              not_null_ptr<ItemInstance> itemInstance) {
    return itemInstance;
}
