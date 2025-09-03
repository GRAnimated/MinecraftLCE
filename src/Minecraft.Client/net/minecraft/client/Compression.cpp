#include "net/minecraft/client/Compression.h"

#include "NX/Platform.h"
#include "net/minecraft/core/System.h"
#include "zlib.h"
#include <string.h>
#include <types.h>

DEFINE_THREAD_STORAGE_SINGLE(Compression)

Compression::Compression() {
    this->dcData = 0;

    // set up flags (guessing)
    struct {
        uint64_t unk;
        uint32_t unk2;
    } XMemFlags;

    XMemFlags.unk = 0x2000000000000;
    XMemFlags.unk2 = 0x20000;

    // IDA wouldn't show this in it's pseudocode... Ghidra did though.
    XMemCreateCompressionContext(PLACEHOLDER, &XMemFlags, 0, &this->XMemCompressionContext);
    XMemCreateDecompressionContext(PLACEHOLDER, &XMemFlags, 0, &this->XMemDecompressionContext);

    this->type = ZLIB;
    this->unk2 = ZLIB;

    InitializeCriticalSection(&this->cMutex);
    InitializeCriticalSection(&this->dcMutex);
}

Compression::~Compression() {
    XMemDestroyCompressionContext(this->XMemCompressionContext);
    XMemDestroyDecompressionContext(this->XMemDecompressionContext);

    nn::os::FinalizeMutex(&this->cMutex);
    nn::os::FinalizeMutex(&this->dcMutex);

    if (this->dcData) {
        delete this->dcData;
    }
}

Compression* Compression::getCompression() {
    return ((ThreadStorage*)TlsGetValue(sThreadStorageIndex))->mStorage;
}

void Compression::SetDecompressionType(ESavePlatform platform) {
    if (platform == Xbox360) {
        Compression::getCompression()->SetType(LZX);
        return;
    }

    if (platform == XBoxOne) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }

    if (platform == WiiU) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }

    if (platform == Switch) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }

    if (platform == PS3) {
        Compression::getCompression()->SetType(DEFLATE);
        return;
    }

    if (platform == PSVita) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }

    if (platform == PS4) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }

    if (platform == PC) {
        Compression::getCompression()->SetType(ZLIB);
        return;
    }
}

int Compression::Compress(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    unsigned int res;
    unsigned long newDestSize;

    // for passing to Zlib
    unsigned long ulDestSize = *dstSize;

    // if dst is nullptr it means we just want size bound
    if (dst) {
        // compress and check for error
        bool zErr = (compress((unsigned char*)dst, &ulDestSize, (unsigned char*)src, srcSize) != Z_OK);

        // move zlib's destSize to our destSize
        newDestSize = ulDestSize;

        // set res
        res = zErr;
    } else {
        // get size bound
        newDestSize = compressBound(srcSize);

        // no error
        res = 0;

        // why?
        ulDestSize = newDestSize;
    }

    // set dstSize to the new size
    *dstSize = newDestSize;

    // if the res code is not negative, we know nothing went wrong.
    return -(res != 0);
}

int Compression::CompressLZXRLE(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    int res;

    nn::os::MutexType* mtx = &this->cMutex;

    EnterCriticalSection(&this->cMutex);

    unsigned char* buf = this->cData;
    unsigned int initDstSize = 0x40000;

    res = internalCompressRle(buf, &initDstSize, src, srcSize);

    if (!res) {
        PIXBeginNamedEvent(0.0, "Secondary compression");
        res = Compress(dst, dstSize, buf, initDstSize);
        PIXEndNamedEvent();
    }

    LeaveCriticalSection(mtx);
    return res;
}

int Compression::Decompress(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    int res;

    if (this->type != this->unk2)
        return DecompressWithType(dst, dstSize, src, srcSize);

    EnterCriticalSection(&this->dcMutex);

    unsigned long ulDestSize = *dstSize;
    res = uncompress((unsigned char*)dst, &ulDestSize, (unsigned char*)src, srcSize);

    *dstSize = ulDestSize;

    LeaveCriticalSection(&this->dcMutex);

    // if not Z_OK, we know there's an error
    if (res)
        return -1;

    return 0;
}

int Compression::DecompressLZXRLE(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    EnterCriticalSection(&this->dcMutex);

    unsigned char* temp;
    unsigned long ulDestSize;
    unsigned int initDstSize = 0x32000;

    ulDestSize = *dstSize;
    if (ulDestSize > 0x32000) {
        initDstSize = *dstSize;
        temp = new unsigned char[ulDestSize];

        Decompress(temp, &initDstSize, src, srcSize);
        internalDecompressRle(dst, dstSize, temp, initDstSize);

        if (temp)
            delete[] temp;
    } else {
        if (!this->dcData) {
            this->dcData = new unsigned char[0x32000];
        }

        Compression::Decompress(this->dcData, &initDstSize, src, srcSize);
        Compression::internalDecompressRle(dst, dstSize, this->dcData, initDstSize);
    }
    LeaveCriticalSection(&this->dcMutex);
    return 0;
}

int Compression::DecompressWithType(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize) {
    // I'm confused... how does this decompress?
    // unless it got ifdef'd out
    if (this->type < 2) {
        memcpy(dst, src, srcSize);
        *dstSize = srcSize;
        return 0;
    }

    return -1;
}

void Compression::VitaVirtualDecompress(void* dst, uint* dstSize, void* src, uint srcSize) {
    unsigned char* srcPtr = (unsigned char*)src;
    unsigned char* dstPtr = (unsigned char*)dst;
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
                // reason (likely) being is that it's not making the file smaller when taking up 3 bytes of
                // space for just 2-3 repeated bytes also the logic also probably allows for files containing
                // 0xFF to not break the compression. (untested)
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

    // thanks 4J for making this specific decompression function return bool, also it always returns false...
    // why?
    return false;
}
