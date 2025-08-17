#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

class CompoundTag;
class DataInput;
class DataOutput;
class InputStream;
class OutputStream;
class Tag;

class NbtIo {
public:
    static Tag* readUnnamedTag(DataInput* input, int unk);
    static CompoundTag* read(DataInput* input);
    static CompoundTag* readCompressed(InputStream* inputStream);
    static void writeUnnamedTag(Tag* tag, DataOutput* output);
    static void write(CompoundTag* tag, DataOutput* output);
    static void writeCompressed(CompoundTag* tag, OutputStream* outputStream);
    static CompoundTag* decompress(arrayWithLength<unsigned char> array);
    static arrayWithLength<unsigned char> compress(CompoundTag* tag);
};
