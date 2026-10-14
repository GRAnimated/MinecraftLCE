#include "com/mojang/nbt/NbtIo.h"
#include "java/io/DataInputStream.h"

CompoundTag* DataInputStream::readNbt() {
    const short length = readShort();
    if (length < 0)
        return nullptr;
    arrayWithLength<unsigned char> bytes(length, true);
    readFully(bytes);
    CompoundTag* result = NbtIo::decompress(bytes);
    delete[] bytes.m_data;
    return result;
}
