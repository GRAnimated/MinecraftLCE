#include "net/minecraft/world/level/saveddata/SavedData.h"

SavedData::SavedData(const std::wstring& path) : m_path(path) {}

SavedData::~SavedData() {}

void SavedData::setDirty(bool isDirty) {
    m_isDirty = isDirty;
}

void SavedData::setDirty() {
    setDirty(true);
}

bool SavedData::isDirty() {
    return m_isDirty;
}
