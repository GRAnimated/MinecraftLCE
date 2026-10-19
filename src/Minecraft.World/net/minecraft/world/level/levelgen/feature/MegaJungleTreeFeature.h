#pragma once

#include "net/minecraft/world/level/levelgen/feature/MegaTreeFeature.h"

class MegaJungleTreeFeature : public MegaTreeFeature {
public:
    MegaJungleTreeFeature(bool update, int minHeight, int heightRange, const BlockState* trunk,
                          const BlockState* leaves);
    ~MegaJungleTreeFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;
    void createCrown(Level*, const BlockPos&, int);
    void placeVine(Level*, Random&, const BlockPos&, const BooleanProperty*);
};
