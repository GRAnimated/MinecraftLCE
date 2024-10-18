#include "Minecraft.World/level/saveddata/SavedData.h"

SavedData::SavedData(std::wstring const& path) : mPath(path) {}

SavedData::~SavedData() {}

void SavedData::setDirty(bool isDirty) {
    mIsDirty = isDirty;
}

void SavedData::setDirty() {
    setDirty(true);
}

bool SavedData::isDirty() {
    return mIsDirty;
}
