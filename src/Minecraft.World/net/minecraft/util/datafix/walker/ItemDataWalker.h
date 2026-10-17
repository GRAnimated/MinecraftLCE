#pragma once

#include "net/minecraft/util/datafix/walker/KeyedDataWalker.h"
#include <vector>

class ItemDataWalker : public KeyedDataWalker {
public:
    // Registry key selection in this constructor is not yet reconstructed.
    ItemDataWalker(eINSTANCEOF, const std::wstring&);
    ~ItemDataWalker() override;
    CompoundTag* doWalk(DataFixer*, CompoundTag*, int version) override;

    std::vector<std::wstring> m_keys;
};

static_assert(sizeof(ItemDataWalker) == 0x70, "Original item walker allocation");
