#pragma once

#include "net/minecraft/world/level/saveddata/SavedData.h"

class CompoundTag;

class StructureFeatureSavedData : public SavedData {
public:
    StructureFeatureSavedData(const std::wstring&);

    virtual void load(CompoundTag*) override;
    virtual void save(CompoundTag*) override;

    CompoundTag* mTag;
};
