#pragma once

#include "net/minecraft/world/entity/ai/behavior/Behavior.h"

#include "types.h"

class BlockSource;
class ItemInstance;

class DispenseItemBehavior : public Behavior {
public:
    DispenseItemBehavior() {}
    ~DispenseItemBehavior() override {}

    virtual not_null_ptr<ItemInstance> dispense(BlockSource* source, not_null_ptr<ItemInstance> item) = 0;
};
