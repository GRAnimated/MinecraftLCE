#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/util/datafix/fixes/ItemTotemRenameFix.h"
#include "net/minecraft/util/datafix/fixes/ItemWaterPotionFix.h"

ItemTotemRenameFix::ItemTotemRenameFix() {}
ItemWaterPotionFix::ItemWaterPotionFix() {}

int ItemTotemRenameFix::getVersion() {
    return 820;
}
int ItemWaterPotionFix::getVersion() {
    return 806;
}

CompoundTag* ItemTotemRenameFix::fix(CompoundTag* tag) {
    if (tag->getString(L"id") == L"minecraft:totem")
        tag->putString(L"id", L"minecraft:totem_of_undying");
    return tag;
}

CompoundTag* ItemWaterPotionFix::fix(CompoundTag* tag) {
    const std::wstring id = tag->getString(L"id");
    if (id == L"minecraft:potion" || id == L"minecraft:splash_potion" || id == L"minecraft:lingering_potion"
        || id == L"minecraft:tipped_arrow") {
        CompoundTag* itemTag = tag->getCompound(L"tag");
        if (!itemTag->contains(L"Potion", Tag::TAG_String))
            itemTag->putString(L"Potion", L"minecraft:water");
        if (!tag->contains(L"tag", Tag::TAG_Compound))
            tag->put(L"tag", itemTag);
    }
    return tag;
}
