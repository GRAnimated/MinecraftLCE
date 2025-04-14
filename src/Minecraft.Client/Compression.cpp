#include <types.h>
#include "Compression.h"
#include <cstdint>

void Compression::VitaVirtualDecompress(void* dst, uint* dstSize, void* src, uint srcSize) {
    uchar* srcPtr = (uchar*)src;
    uchar* dstPtr = (uchar*)dst;
    int dstOffset = 0;
    int index = 0;

    // while we haven't reached the end of the input data
    for (index = 0; index != srcSize; index++) {
        // check if the current byte is not zero
        if (srcPtr[index]) {
            // if it is not zero, copy the byte to the output buffer
            dstPtr[dstOffset++] = srcPtr[index];
        } else {
            // read the count
            uint count = srcPtr[++index];

            // write `count` amount of zeroes to the output buffer
            for (int z = 0; z < count; ++z) {
                dstPtr[dstOffset++] = 0;
            }
        }
    }
    
    // set the dstSize to how many bytes we wrote to the output buffer
    *dstSize = dstOffset;
}

bool Compression::internalDecompressRle(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    unsigned char* dst8 = static_cast<unsigned char*>(dst);
    unsigned char* src8 = static_cast<unsigned char*>(src);
    unsigned char* dstOffset = dst8;

    // if srcSize isn't 0 (because otherwise there's nothing to do)
    if (srcSize != 0) {
        // get the end of the input buffer
        unsigned char* srcEnd = src8 + srcSize;
        // while we haven't reached the end of the input buffer
        while (src8 != srcEnd) {
            // if the current byte is 0xff, we should decompress
            unsigned char val = *src8++;
            if (val == 0xFF) {
                // compressed
                unsigned char count = *src8++;
                unsigned char repeatValue;

                // if count is bigger than 3, we should repeat the next byte count times
                // reason (likely) being is that it's not making the file smaller when taking up 3 bytes of space for just 2-3 repeated bytes
                // also the logic also probably allows for files containing 0xFF to not break the compression. (untested)
                if (count < 3) {
                    repeatValue = 0xff;
                } else {
                    repeatValue = *src8++;
                }

                // write value count times
                for (int i = 0; i <= count; ++i) {
                    *dstOffset++ = repeatValue;
                }
            } else {
                // write normal byte
                *dstOffset++ = val;
            }
        }
    }

    // set the dstSize to how many bytes we wrote to the output buffer
    *dstSize = dstOffset - dst8;

    // thanks 4J for making this specific decompression function return bool, also it always returns false... why?
    return false;
}