#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class MegaTreeFeature : public AbstractTreeFeature {
protected:
    int m_heightRange;
};

ASSERT_SIZEOF(MegaTreeFeature, 0x30)
