#include "net/minecraft/util/datafix/DataFixers.h"
#include "net/minecraft/util/datafix/walker/ItemDataWalker.h"
#include "net/minecraft/util/datafix/walker/ItemListDataWalker.h"

ItemDataWalker::~ItemDataWalker() {}
ItemListDataWalker::~ItemListDataWalker() {}

CompoundTag* ItemDataWalker::doWalk(DataFixer* fixer, CompoundTag* tag, int version) {
    for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
        tag = DataFixers::updateItem(fixer, tag, version, *it);
    return tag;
}

CompoundTag* ItemListDataWalker::doWalk(DataFixer* fixer, CompoundTag* tag, int version) {
    for (auto it = m_keys.begin(); it != m_keys.end(); ++it)
        tag = DataFixers::updateItems(fixer, tag, version, *it);
    return tag;
}
