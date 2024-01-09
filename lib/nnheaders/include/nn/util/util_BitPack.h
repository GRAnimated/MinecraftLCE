#pragma once

#include <nn/types.h>

namespace nn::util {

template <class StorageT, class Tag = void>
struct BitPack {
    StorageT storage;

    void SetBit(int p, bool on) {
        int mask = MakeMask(p);
        if (on) {
            storage |= mask;
        } else {
            storage &= ~mask;
        }
    }

    bool GetBit(int p) const { return IsAnyBitOn(MakeMask(p)); }

    void Clear() { storage = 0; }

    void SetMaskedBits(int, int);
    int GetMaskedBits(int) const;
    void SetAllBitOn(int);
    void SetAllBitOff(int);
    bool IsAllBitOn(int) const;
    bool IsAllBitOff(int) const;

    bool IsAnyBitOn(int mask) const { return static_cast<int>(storage & mask) == mask; }
    bool IsAnyBitOff(int mask) const { return static_cast<int>(storage & mask) != mask; }

    template <int BitPos, int BitWidth, class T>
    struct Field {
        static const int Pos = BitPos;
        static const int Next = BitPos + 1;
        static const int Mask = 1 << BitPos;
        static const int Width = BitWidth;

        typedef T Type;
    };

private:
    static int MakeMask(int p) { return 1 << p; }

    Tag ReadValue(bool*, int, int) const;
};

typedef BitPack<u8> BitPack8;
typedef BitPack<u16> BitPack16;
typedef BitPack<u32> BitPack32;

}  // namespace nn::util