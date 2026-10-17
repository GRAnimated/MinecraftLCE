#include "com/mojang/nbt/NbtIo.h"
#include "java/io/DataOutputStream.h"

void DataOutputStream::writeNbt(CompoundTag* tag) {
    if (!tag) {
        writeShort(-1);
        return;
    }
    arrayWithLength<unsigned char> bytes = NbtIo::compress(tag);
    writeShort(bytes.m_length);
    write(bytes);
    delete[] bytes.m_data;
}
