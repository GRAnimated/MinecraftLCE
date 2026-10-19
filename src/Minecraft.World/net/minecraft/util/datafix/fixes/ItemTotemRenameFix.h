#pragma once

#include "net/minecraft/util/datafix/DataFix.h"

class ItemTotemRenameFix : public DataFix {
public:
    ItemTotemRenameFix();
    int getVersion() override;
    CompoundTag* fix(CompoundTag*) override;
};
