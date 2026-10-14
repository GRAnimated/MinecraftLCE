#pragma once

#include "net/minecraft/util/datafix/walker/KeyedDataWalker.h"
#include <vector>

class ItemListDataWalker : public KeyedDataWalker {
public:
    // Registry key selection in these constructors is not yet reconstructed.
    ItemListDataWalker(eINSTANCEOF, const std::wstring&);
    ItemListDataWalker(eINSTANCEOF, const std::vector<std::wstring>&);
    ~ItemListDataWalker() override;
    CompoundTag* doWalk(DataFixer*, CompoundTag*, int version) override;

    std::vector<std::wstring> m_keys;
};

static_assert(sizeof(ItemListDataWalker) == 0x70, "Original list walker allocation");
