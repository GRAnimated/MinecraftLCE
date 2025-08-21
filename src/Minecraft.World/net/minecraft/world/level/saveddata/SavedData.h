#pragma once

#include <memory>
#include <string>

class CompoundTag;

class SavedData : public std::enable_shared_from_this<SavedData> {
public:
    SavedData(const std::wstring&);
    virtual ~SavedData();
    virtual void load(CompoundTag*) = 0;
    virtual void save(CompoundTag*) = 0;

    void setDirty(bool);
    void setDirty();
    bool isDirty();

    std::wstring mPath;
    bool mIsDirty = false;
};
