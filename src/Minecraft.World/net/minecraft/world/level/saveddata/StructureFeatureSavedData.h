#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/saveddata/SavedData.h"

class CompoundTag;

class StructureFeatureSavedData : public SavedData {
public:
    StructureFeatureSavedData(const std::wstring&);
    ~StructureFeatureSavedData() override;

    void load(CompoundTag*) override;
    CompoundTag* save(CompoundTag*) override;

    static std::wstring createFeatureTagId(int chunkX, int chunkZ);
    void putFeatureTag(arrayWithLength<unsigned char>, int chunkX, int chunkZ);
    CompoundTag* getFullTag();

    static std::wstring FEATURES_KEY;

    CompoundTag* mTag;
};

static_assert(sizeof(StructureFeatureSavedData) == 0x40, "Structure saved-data layout");
