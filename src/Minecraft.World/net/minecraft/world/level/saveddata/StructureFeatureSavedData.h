#pragma once

#include "net/minecraft/world/level/saveddata/SavedData.h"

class CompoundTag;

class StructureFeatureSavedData : public SavedData {
public:
    StructureFeatureSavedData(const std::wstring&);

    void load(CompoundTag*) override;
    void save(CompoundTag*) override;

    CompoundTag* mTag;
};
