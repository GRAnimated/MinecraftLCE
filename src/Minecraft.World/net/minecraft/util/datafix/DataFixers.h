#pragma once

#include <string>

class CompoundTag;
class DataFixer;
class DataFixerUpper;

class DataFixers {
public:
    static DataFixerUpper* createFixerUpper();
    static CompoundTag* updateItem(DataFixer*, CompoundTag*, int version, const std::wstring& key);
    static CompoundTag* updateItems(DataFixer*, CompoundTag*, int version, const std::wstring& key);
};
