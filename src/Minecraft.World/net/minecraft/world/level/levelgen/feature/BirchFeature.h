#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

class BirchFeature : public AbstractTreeFeature {
public:
    BirchFeature(bool update, bool superBirch);
    static void staticCtor();
    bool place(Level*, Random&, const BlockPos&) override;

    static const BlockState* TRUNK;
    static const BlockState* LEAVES;

private:
    bool m_superBirch;
};

ASSERT_SIZEOF(BirchFeature, 0x30)
