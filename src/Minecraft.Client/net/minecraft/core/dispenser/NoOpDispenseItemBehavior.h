#pragma once

#include "net/minecraft/core/dispenser/DispenseItemBehavior.h"

class NoOpDispenseItemBehavior : public DispenseItemBehavior {
public:
    NoOpDispenseItemBehavior() {}
    ~NoOpDispenseItemBehavior() override {}

    not_null_ptr<ItemInstance> dispense(BlockSource* source,
                                        not_null_ptr<ItemInstance> itemInstance) override;
};
