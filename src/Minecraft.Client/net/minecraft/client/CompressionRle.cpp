#include "net/minecraft/client/Compression.h"

#include "NX/Platform.h"

int Compression::internalCompressRle(void* dst, uint* dstSize, void* src, uint srcSize) {
    unsigned char* output = static_cast<unsigned char*>(dst);
    unsigned char* const begin = output;
    unsigned char* input = static_cast<unsigned char*>(src);
    const uint capacity = *dstSize;
    PIXBeginNamedEvent(0.0f, "RLE compression");
    unsigned char* const end = input + srcSize;
    for (;;) {
        const unsigned char value = *input;
        uint count = 1;
        while (input + count != end && count < 256 && input[count] == value)
            ++count;
        input += count;
        if (count >= 4) {
            *output++ = 0xff;
            *output++ = static_cast<unsigned char>(count - 1);
            *output++ = value;
        } else if (value == 0xff) {
            *output++ = 0xff;
            *output++ = static_cast<unsigned char>(count - 1);
        } else {
            for (uint i = 0; i < count; ++i)
                *output++ = value;
        }
        const bool more = input != end;
        const uint written = static_cast<uint>(output - begin);
        const bool full = output >= begin + capacity - 3;
        if (!more || full) {
            PIXEndNamedEvent();
            *dstSize = written;
            return more ? static_cast<int>(0x80cc0001u) : 0;
        }
    }
}
