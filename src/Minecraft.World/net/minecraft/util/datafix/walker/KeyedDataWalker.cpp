#include "net/minecraft/util/datafix/walker/KeyedDataWalker.h"

#include "com/mojang/nbt/CompoundTag.h"

KeyedDataWalker::~KeyedDataWalker() {}

CompoundTag* KeyedDataWalker::walk(DataFixer* fixer, CompoundTag* tag, int version) {
    if (ResourceLocation(tag->getString(L"id")) == &m_key)
        return doWalk(fixer, tag, version);
    return tag;
}
