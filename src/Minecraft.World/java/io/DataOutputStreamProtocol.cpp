#include "java/io/DataOutputStream.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"

void DataOutputStream::writeBlockPos(const BlockPos& pos) {
    writeLong(pos.compressBlockPos());
}

void DataOutputStream::writeItem(not_null_ptr<ItemInstance> item) {
    if (item->isEmpty()) {
        writeShort(-1);
        return;
    }
    writeShort(Item::VALIDgetId(item->getItem()));
    writeByte(item->getCount());
    writeShort(item->getAuxValue());
    writeNbt(item->getTag());
}
