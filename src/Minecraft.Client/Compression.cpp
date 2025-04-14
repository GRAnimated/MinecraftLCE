#include <types.h>
#include "Compression.h"

void Compression::VitaVirtualDecompress(void* dest, uint* destSize, void* src, uint srcSize) {
    uchar* srcPtr = (uchar*)src;
    uchar* destPtr = (uchar*)dest;
    int destOffset = 0;
    int index = 0;

    // while we haven't reached the end of the input data
    for (index = 0; index != srcSize; index++) {
        // check if the current byte is not zero
        if (srcPtr[index]) {
            // if it is not zero, copy the byte to the output buffer
            destPtr[destOffset++] = srcPtr[index];
        } else {
            // read the count
            uint count = srcPtr[++index];

            // write `count` amount of zeroes to the output buffer
            for (int z = 0; z < count; ++z) {
                destPtr[destOffset++] = 0;
            }
        }
    }
    
    // set the destSize to how many bytes we wrote to the output buffer
    *destSize = destOffset;
}