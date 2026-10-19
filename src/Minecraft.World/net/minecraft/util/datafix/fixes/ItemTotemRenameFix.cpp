#include "net/minecraft/util/datafix/fixes/ItemTotemRenameFix.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/util/datafix/fixes/ItemWaterPotionFix.h"

// name guessed
ItemTotemRenameFix::ItemTotemRenameFix() {}

// name guessed
int ItemTotemRenameFix::getVersion() {
    return 820;
}

// name guessed
CompoundTag* ItemTotemRenameFix::fix(CompoundTag* tag) {
    if (tag->getString(L"id") == L"minecraft:totem")
        tag->putString(L"id", L"minecraft:totem_of_undying");
    return tag;
}
