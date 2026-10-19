#pragma once

class CompoundTag;

class DataFix {
public:
    DataFix();
    virtual ~DataFix();
    virtual int getVersion() = 0;
    virtual CompoundTag* fix(CompoundTag*) = 0;
};
