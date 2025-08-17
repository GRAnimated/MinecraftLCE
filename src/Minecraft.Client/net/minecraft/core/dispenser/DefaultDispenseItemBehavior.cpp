#include "net/minecraft/core/dispenser/DefaultDispenseItemBehavior.h"

#include "net/minecraft/core/BlockSource.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/Random.h"
#include "net/minecraft/world/entity/item/ItemEntity.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/block/DispenserBlock.h"
#include "net/minecraft/world/level/block/state/BlockState.h"

not_null_ptr<ItemInstance> DefaultDispenseItemBehavior::dispense(BlockSource* blockSource,
                                                                 not_null_ptr<ItemInstance> itemInstance) {
    eOUTCOME outcome = SUCCESS;

    not_null_ptr<ItemInstance> newInstance = execute(blockSource, itemInstance, outcome);
    playSound(blockSource, outcome);
    playAnimation(blockSource,
                  blockSource->getBlockState()->getValue<Direction*>((Property*)DispenserBlock::FACING),
                  outcome);
    return newInstance;
}

not_null_ptr<ItemInstance> DefaultDispenseItemBehavior::execute(BlockSource* blockSource,
                                                                not_null_ptr<ItemInstance> itemInstance,
                                                                eOUTCOME& outcome) {
    Direction* direction
        = blockSource->getBlockState()->getValue<Direction*>((Property*)DispenserBlock::FACING);
    Position* position = DispenserBlock::getDispensePosition(blockSource);

    not_null_ptr<ItemInstance> newInstance = itemInstance->split(1);

    Level* level = blockSource->getWorld();
    DefaultDispenseItemBehavior::spawnItem(level, newInstance, 6, direction, position);

    delete position;

    outcome = SUCCESS;

    return itemInstance;
}

void DefaultDispenseItemBehavior::playSound(BlockSource* blockSource, eOUTCOME outcome) {
    if (outcome != FAILURE) {
        blockSource->getWorld()->levelEvent(1000, blockSource->getPos(), 0);
    } else {
        blockSource->getWorld()->levelEvent(1001, blockSource->getPos(), 0);
    }
}

void DefaultDispenseItemBehavior::playAnimation(BlockSource* blockSource, const Direction* direction,
                                                eOUTCOME outcome) {
    if (outcome == FAILURE)
        return;

    blockSource->getWorld()->levelEvent(2000, blockSource->getPos(), getLevelEventDataFrom(direction));
}

int DefaultDispenseItemBehavior::getLevelEventDataFrom(const Direction* direction) {
    return direction->getX() + 3 * direction->getZ() + 4;
}

// NON_MATCHING: Extra nullptr needs to be passed into the shared_ptr constructor
void DefaultDispenseItemBehavior::spawnItem(Level* level, not_null_ptr<ItemInstance> itemInstance, int count,
                                            const Direction* direction, Position* position) {
    double x = position->getX();
    double y = position->getY();
    double z = position->getZ();

    if (direction->getAxis() == Direction::Axis::Y) {
        y -= 0.125;
    } else {
        y -= 0.15625;
    }

    not_null_ptr<ItemEntity> itemEntity
        = not_null_ptr<ItemEntity>(new ItemEntity(level, x, y, z, itemInstance));

    double randomFactor = level->mRandom->nextDouble() * 0.1 + 0.2;
    itemEntity->mDeltaMovementX = direction->getX() * randomFactor;
    itemEntity->mDeltaMovementY = 0.2f;
    itemEntity->mDeltaMovementZ = randomFactor * direction->getZ();
    itemEntity->mDeltaMovementX += level->mRandom->nextGaussian() * 0.0075f * count;
    itemEntity->mDeltaMovementY += level->mRandom->nextGaussian() * 0.0075f * count;
    itemEntity->mDeltaMovementZ += level->mRandom->nextGaussian() * 0.0075f * count;

    level->addEntity(itemEntity);
}
