#include "java/io/DataInputStream.h"
#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"

BlockPos DataInputStream::readBlockPos() {
    return BlockPos::decompressBlockPos(readLong());
}

BlockPos* DataInputStream::readBlockPosPointer() {
    const BlockPos pos = BlockPos::decompressBlockPos(readLong());
    return new BlockPos(pos.getX(), pos.getY(), pos.getZ());
}

not_null_ptr<ItemInstance> DataInputStream::readItem() {
    not_null_ptr<ItemInstance> result = ItemInstance::EMPTY;
    const short id = readShort();
    if (id >= 0) {
        const unsigned char count = readByte();
        const short auxiliary = readShort();
        result = not_null_ptr<ItemInstance>(new ItemInstance(Item::byId(id), count, auxiliary));
        result->setTag(readNbt());
    }
    return result;
}
