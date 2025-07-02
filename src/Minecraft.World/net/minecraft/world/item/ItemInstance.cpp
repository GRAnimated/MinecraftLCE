#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"

ItemInstance::ItemInstance(Block* block) {
    this->init(Item::byBlock(block), 1, 0);
}

ItemInstance::ItemInstance(Block* block, int count) {
    this->init(Item::byBlock(block), count, block->convertBlockStateToLegacyData(block->defaultBlockState()));
}

ItemInstance::ItemInstance(Block* block, int count, int aux) {
    this->init(Item::byBlock(block), count, aux);
}

ItemInstance::ItemInstance(Item* item) {
    this->init(item, 1, 0);
}

ItemInstance::ItemInstance(Item* item, int count) {
    this->init(item, count, 0);
}

ItemInstance::ItemInstance(Item* item, int count, int aux) {
    this->init(item, count, aux);
}

ItemInstance::ItemInstance(CompoundTag* compoundTag) {
    this->init(nullptr, 0, 0);
    this->mItem = Item::byString(compoundTag->getString(L"id"));
    this->dword_14 = 0;
    this->mCount = compoundTag->getByte(L"Count");
    this->mDamage = compoundTag->getShort(L"Damage");

    if ((this->mDamage & 0x80000000) != 0)
        this->mDamage = 0;

    if (compoundTag->contains(L"tag", 10)) {
        if (this->mTag)
            delete this->mTag;

        this->mTag = compoundTag->getCompound(L"tag")->copy();

        if (this->mItem)
            this->mItem->verifyTagAfterLoad(this->mTag);
    }
    this->updateEmptyCacheFlag();
}