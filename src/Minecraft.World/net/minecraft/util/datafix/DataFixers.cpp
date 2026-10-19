#include "net/minecraft/util/datafix/DataFixers.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/ListTag.h"
#include "net/minecraft/util/datafix/DataFixer.h"

// name guessed
CompoundTag* DataFixers::updateItem(DataFixer* fixer, CompoundTag* tag, int version,
                                    const std::wstring& key) {
    if (tag->contains(key, Tag::TAG_Compound)) {
        tag->put(key, fixer->update(DataFixTypes::ITEM, tag->getCompound(key), version));
    }
    return tag;
}

// name guessed
CompoundTag* DataFixers::updateItems(DataFixer* fixer, CompoundTag* tag, int version,
                                     const std::wstring& key) {
    if (tag->contains(key, Tag::TAG_List)) {
        ListTag* list = tag->getList(key, Tag::TAG_Compound);
        for (int index = 0; index < static_cast<int>(list->size()); ++index) {
            list->set(index, fixer->update(DataFixTypes::ITEM, list->getCompound(index), version));
        }
    }
    return tag;
}
