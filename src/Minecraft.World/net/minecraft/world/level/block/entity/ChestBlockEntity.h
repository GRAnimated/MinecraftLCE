#pragma once

#include "net/minecraft/world/level/block/entity/RandomizableLockableContainerBlockEntity.h"

class ChestBlockEntity : public RandomizableLockableContainerBlockEntity {
public:
    char m_unknown68[0x30];
    bool m_isBonusChest;
};

ASSERT_SIZEOF(ChestBlockEntity, 0xA0)
