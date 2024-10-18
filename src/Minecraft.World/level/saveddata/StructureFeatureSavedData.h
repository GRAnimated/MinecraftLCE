#pragma once

#include "Minecraft.World/level/saveddata/SavedData.h"

class CompoundTag;

class StructureFeatureSavedData : public SavedData {
public:
    StructureFeatureSavedData(std::wstring const&);

    virtual void load(CompoundTag*) override;
    virtual void save(CompoundTag*) override;

    CompoundTag* mTag;
};
