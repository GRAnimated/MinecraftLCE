#pragma once

class BlockState;
class CompoundTag;

class NbtUtils {
public:
    // Switch registry/property decoder at 0x71006ef4b0.
    static const BlockState* readBlockState(CompoundTag*);
};
