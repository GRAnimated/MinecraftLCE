#pragma once

#include "net/minecraft/world/level/levelgen/feature/AbstractTreeFeature.h"

// Only the selector-facing interface is recovered; the feature body is still missing.
class BigTreeFeature : public AbstractTreeFeature {
public:
    BigTreeFeature(bool update);
    ~BigTreeFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;

private:
    // Switch allocation and constructor stores establish the remaining 0x80 bytes.
    char m_unrecoveredState[0x80];
};

ASSERT_SIZEOF(BigTreeFeature, 0xa8)
