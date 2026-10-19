#pragma once

#include "net/minecraft/util/datafix/DataFixer.h"
#include <string>
#include <unordered_map>
#include <vector>

class CompoundTag;
class DataFix;
class DataWalker;

class DataFixerUpper : public DataFixer {
public:
    explicit DataFixerUpper(int version);
    CompoundTag* updateData(DataFixTypes::EDataFixTypes, CompoundTag*);
    CompoundTag* update(DataFixTypes::EDataFixTypes, CompoundTag*, int version) override;
    CompoundTag* applyFixes(DataFixTypes::EDataFixTypes, CompoundTag*, int version);
    CompoundTag* applyWalkers(DataFixTypes::EDataFixTypes, CompoundTag*, int version);
    std::vector<DataWalker*>* getOrCreateWalker(DataFixTypes::EDataFixTypes);
    std::vector<DataFix*>* getOrCreateFix(DataFixTypes::EDataFixTypes);
    void addWalker(DataFixTypes::EDataFixTypes, DataWalker*);
    void addFixer(DataFixTypes::EDataFixTypes, DataFix*);

    int m_version;
    std::unordered_map<DataFixTypes::EDataFixTypes, std::vector<DataWalker*>*> m_walkers;
    std::unordered_map<DataFixTypes::EDataFixTypes, std::vector<DataFix*>*> m_fixes;
    static const std::wstring DATA_VERSION_KEY;
};

static_assert(sizeof(DataFixerUpper) == 0x60, "Original fixer-upper allocation");
static_assert(__builtin_offsetof(DataFixerUpper, m_version) == 8, "Original target-version offset");
static_assert(__builtin_offsetof(DataFixerUpper, m_walkers) == 0x10, "Original walker registry offset");
static_assert(__builtin_offsetof(DataFixerUpper, m_fixes) == 0x38, "Original fix registry offset");
