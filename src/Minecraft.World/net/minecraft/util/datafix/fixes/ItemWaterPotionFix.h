#pragma once

#include "net/minecraft/util/datafix/DataFix.h"

class ItemWaterPotionFix : public DataFix {
public:
    ItemWaterPotionFix();
    int getVersion() override;
    CompoundTag* fix(CompoundTag*) override;
};
