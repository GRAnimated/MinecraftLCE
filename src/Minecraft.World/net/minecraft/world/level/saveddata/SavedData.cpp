#include "net/minecraft/world/level/saveddata/SavedData.h"

SavedData::SavedData(const std::wstring& path) : mPath(path) {}

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
