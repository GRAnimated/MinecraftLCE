#include "com/mojang/nbt/NbtIo.h"
#include "java/io/DataInputStream.h"
#include "net/minecraft/client/Compression.h"

CompoundTag* DataInputStream::readCompressedNbt() {
    const short length = readShort();
    if (length < 0)
        return nullptr;
    const short compressedLength = readShort();
    if (compressedLength < 0)
        return nullptr;
    arrayWithLength<unsigned char> compressed(compressedLength, true);
    readFully(compressed);
    arrayWithLength<unsigned char> bytes(length, true);
    unsigned int actualLength = length;
    Compression::getCompression()->Decompress(bytes.m_data, &actualLength, compressed.m_data,
                                              compressed.m_length);
    CompoundTag* result = NbtIo::decompress(bytes);
    delete[] bytes.m_data;
    delete[] compressed.m_data;
    return result;
}
