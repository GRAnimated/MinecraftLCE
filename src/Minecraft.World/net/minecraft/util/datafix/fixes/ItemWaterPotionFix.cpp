#include "net/minecraft/util/datafix/fixes/ItemWaterPotionFix.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/util/datafix/fixes/ItemTotemRenameFix.h"

// name guessed
ItemWaterPotionFix::ItemWaterPotionFix() {}

// name guessed
int ItemWaterPotionFix::getVersion() {
    return 806;
}

// name guessed
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
