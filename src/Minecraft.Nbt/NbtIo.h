#pragma once

class CompoundTag;
class DataOutput;

class NbtIo {
public:
    static void write(CompoundTag* tag, DataOutput* out);
};
