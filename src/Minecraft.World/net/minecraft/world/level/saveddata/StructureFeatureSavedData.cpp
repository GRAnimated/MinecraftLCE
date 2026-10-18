#include "net/minecraft/world/level/saveddata/StructureFeatureSavedData.h"

#include "com/mojang/nbt/CompoundTag.h"

std::wstring StructureFeatureSavedData::FEATURES_KEY = L"Features";

StructureFeatureSavedData::StructureFeatureSavedData(const std::wstring& path) : SavedData(path) {
    mTag = new CompoundTag();
}

StructureFeatureSavedData::~StructureFeatureSavedData() {
    delete mTag;
}

void StructureFeatureSavedData::load(CompoundTag* root) {
    delete mTag;
    bool present = root->contains(FEATURES_KEY);
    CompoundTag* features = root->getCompound(FEATURES_KEY);
    // getCompound creates an owned empty tag when the key is absent.
    mTag = present ? features->copy() : features;
}

CompoundTag* StructureFeatureSavedData::save(CompoundTag* root) {
    root->put(FEATURES_KEY, mTag->copy());
    return root;
}

std::wstring StructureFeatureSavedData::createFeatureTagId(int chunkX, int chunkZ) {
    return L"[" + std::to_wstring(chunkX) + L"," + std::to_wstring(chunkZ) + L"]";
}

void StructureFeatureSavedData::putFeatureTag(arrayWithLength<unsigned char> data, int chunkX, int chunkZ) {
    mTag->putByteArray(createFeatureTagId(chunkX, chunkZ), data);
}

CompoundTag* StructureFeatureSavedData::getFullTag() {
    return mTag;
}
