#pragma once

#include "net/minecraft/util/datafix/DataFixTypes.h"

class CompoundTag;

class DataFixer {
public:
    DataFixer();
    virtual CompoundTag* update(DataFixTypes::EDataFixTypes, CompoundTag*, int version) = 0;
};
