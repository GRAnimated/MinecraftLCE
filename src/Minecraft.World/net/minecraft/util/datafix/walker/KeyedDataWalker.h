#pragma once

#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/util/datafix/walker/DataWalker.h"

class KeyedDataWalker : public DataWalker {
public:
    /** Entity/block-entity registry key selection is not reconstructed here.
     */
    explicit KeyedDataWalker(eINSTANCEOF);
    ~KeyedDataWalker() override;
    CompoundTag* walk(DataFixer*, CompoundTag*, int version) override;
    virtual CompoundTag* doWalk(DataFixer*, CompoundTag*, int version) = 0;

    ResourceLocation m_key;
};

static_assert(sizeof(KeyedDataWalker) == 0x58, "Original keyed walker allocation");
