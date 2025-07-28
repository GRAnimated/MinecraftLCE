#pragma once

#include "net/minecraft/core/dispenser/DispenseItemBehavior.h"

class Direction;
class Level;
class Position;

class DefaultDispenseItemBehavior : public DispenseItemBehavior {
public:
    enum eOUTCOME {
        SUCCESS = 1,  // SoundEvents::DISPENSER_DISPENSE is played when the outcome isn't FAILURE
        FAILURE = 2,  // SoundEvents::DISPENSER_FAIL
    };

    DefaultDispenseItemBehavior() {}
    ~DefaultDispenseItemBehavior() override {}

    not_null_ptr<ItemInstance> dispense(BlockSource* blockSource,
                                        not_null_ptr<ItemInstance> itemInstance) override;
    virtual not_null_ptr<ItemInstance> execute(BlockSource* blockSource,
                                               not_null_ptr<ItemInstance> itemInstance, eOUTCOME& outcome);
    virtual void playSound(BlockSource* blockSource, eOUTCOME outcome);
    virtual void playAnimation(BlockSource* blockSource, const Direction* direction, eOUTCOME outcome);
    virtual int getLevelEventDataFrom(const Direction* direction);

    static void spawnItem(Level*, not_null_ptr<ItemInstance>, int, const Direction*, Position*);
};
