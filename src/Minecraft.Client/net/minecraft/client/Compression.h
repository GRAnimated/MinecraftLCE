#pragma once

#include "net/minecraft/client/ESavePlatform.h"
#include "net/minecraft/util/ThreadStorage.h"
#include "types.h"
#include <nn/os.h>

class Compression {
public:
    enum ECompressionTypes : unsigned int { LZX = 2, ZLIB = 3, DEFLATE = 4 };

    DECLARE_THREAD_STORAGE_SINGLE(Compression)

    Compression();
    ~Compression();

    static Compression* getCompression();

    void SetDecompressionType(ESavePlatform platform);

    void SetType(ECompressionTypes type) { this->m_type = type; }

    /// @brief Compresses src data with Zlib (if dst is not nullptr)
    /// @param dst Output buffer to store compressed data, optionally can be nullptr if you just want size
    /// bound
    /// @param dstSize Pointer to uint to store the size of the compressed data
    /// @param src Pointer to the input data
    /// @param srcSize The size of the input data
    int Compress(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize);

    int CompressLZXRLE(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize);

    int Decompress(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize);

    int DecompressLZXRLE(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize);

    int DecompressWithType(void* dst, unsigned int* dstSize, void* src, unsigned int srcSize);

    /// @brief Decompresses "Vita RLE"
    /// @param dst Output buffer to store decompressed data
    /// @param dstSize Pointer to uint to store the size of the decompressed data
    /// @param src Pointer to the input compressed data
    /// @param srcSize The size of the input data
    static void VitaVirtualDecompress(void* dst, uint* dstSize, void* src, uint srcSize);

    /// @brief Decompresses Internal RLE, mainly used for chunks.
    /// @param dst Output buffer to store decompressed data
    /// @param dstSize Pointer to uint to store the size of the decompressed data
    /// @param src Pointer to the input compressed data
    /// @param srcSize The size of the input data
    /// @returns `false` if there was no error, otherwise `true` (assumed, in reality it always returns
    /// `false`)
    static bool internalDecompressRle(void* dst, uint* dstSize, void* src, uint srcSize);

    static int internalCompressRle(void* dst, uint* dstSize, void* src, uint srcSize);

private:
    void* m_xMemCompressionContext;
    void* m_xMemDecompressionContext;
    nn::os::MutexType m_cMutex;   // compression mutex
    nn::os::MutexType m_dcMutex;  // decompression mutex
    unsigned char m_cData[0x40000];
    unsigned char* m_dcData;  // devs only allocate 0x32000 for this, why?
    ECompressionTypes m_type;
    ECompressionTypes m_unk2;  // set same as type initially, also compared against it. Could be something
                               // like initType or whatever.
};
