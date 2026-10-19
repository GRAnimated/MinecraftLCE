#pragma once

#include "net/minecraft/world/level/block/BaseEntityBlock.h"
#include "net/minecraft/world/level/block/state/IntegerProperty.h"

class EndGatewayBlock : public BaseEntityBlock {
public:
    static IntegerProperty* FJ_PORTAL_NUMBER;
    EndGatewayBlock(Material*);
};
