#pragma once

#include "net/minecraft/world/level/levelgen/feature/MegaTreeFeature.h"

class MegaJungleTreeFeature : public MegaTreeFeature {
public:
    MegaJungleTreeFeature(bool update, int minHeight, int heightRange, const BlockState* trunk,
                          const BlockState* leaves);
    bool place(Level*, Random&, const BlockPos&) override;
};
