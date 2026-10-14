#include "NX/Platform.h"
#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/NbtIo.h"
#include "java/io/BufferedOutputStream.h"
#include "java/io/ByteArrayInputStream.h"
#include "java/io/ByteArrayOutputStream.h"
#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/core/System.h"
#include <cstring>

CompoundTag* NbtIo::readCompressed(InputStream* inputStream) {
    MemSect(26);
    DataInputStream dataInputStream(inputStream);
    CompoundTag* tag = read(&dataInputStream);
    dataInputStream.close();
    MemSect(0);
    return tag;
}

void NbtIo::writeCompressed(CompoundTag* tag, OutputStream* outputStream) {
    BufferedOutputStream bufferedOutputStream(outputStream, 1024);

    DataOutputStream dataOutputStream(&bufferedOutputStream);
    NbtIo::write((CompoundTag*)tag, &dataOutputStream);

    dataOutputStream.close();
}

CompoundTag* NbtIo::decompress(arrayWithLength<unsigned char> array) {
    ByteArrayInputStream byteArrayInputStream(array);
    DataInputStream dataInputStream(&byteArrayInputStream);

    CompoundTag* tag = NbtIo::read(&dataInputStream);
    // The target resets its borrowed array view before destroying the stream.
    // 0x7100016654 was named as a default constructor, but preserves the vptr.
    byteArrayInputStream.reset();
    dataInputStream.close();

    return tag;
}

arrayWithLength<unsigned char> NbtIo::compress(CompoundTag* tag) {
    ByteArrayOutputStream byteArrayOutputStream;
    DataOutputStream dataOutputStream(&byteArrayOutputStream);

    NbtIo::write(tag, &dataOutputStream);

    arrayWithLength<unsigned char> compressedData(byteArrayOutputStream.size(), true);
    System::arraycopy(byteArrayOutputStream.m_buffer, 0, &compressedData, 0, byteArrayOutputStream.size());

    dataOutputStream.close();

    return compressedData;
}
