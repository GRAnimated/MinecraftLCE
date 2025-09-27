#pragma once

#include "LockableContainerBlockEntity.h"
#include "net/minecraft/world/WorldlyContainer.h"

// BLOCK STUB
class BeaconBlockEntity : public LockableContainerBlockEntity, public WorldlyContainer {
public:
    static void staticCtor();
};
