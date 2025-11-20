#pragma once

#include "net/minecraft/world/WorldlyContainer.h"
#include "net/minecraft/world/level/block/entity/LockableContainerBlockEntity.h"

// BLOCK STUB
class BeaconBlockEntity : public LockableContainerBlockEntity, public WorldlyContainer {
public:
    static void staticCtor();
};
