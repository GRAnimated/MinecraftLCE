#pragma once

#include "platform/NX/Platform.h"
#include "Minecraft.Core/System.h"
#include "zlib/zlib.h"
#include "ESavePlatform.h"

class Compression {
public:
    enum ECompressionTypes : unsigned int {
        LZX = 2,
        ZLIB = 3,
        DEFLATE = 4
    };

    class ThreadStorage {
    public:
        Compression *compression;

        ThreadStorage();
        ~ThreadStorage();
    };

    Compression();
    ~Compression();

    // Thread Storage shit
    static unsigned int tlsIndex;
    static Compression::ThreadStorage *threadStorage;

    static void CreateNewThreadStorage();
    static void ReleaseThreadStorage();
    static void UseDefaultThreadStorage();
    static Compression *getCompression();

    void SetDecompressionType(ESavePlatform platform);

    void SetType(ECompressionTypes type) { this->type = type; };

    /// @brief Compresses src data with Zlib (if dst is not nullptr)
    /// @param dst Output buffer to store compressed data, optionally can be nullptr if you just want size bound
    /// @param dstSize Pointer to uint to store the size of the compressed data
    /// @param src Pointer to the input data
    /// @param srcSize The size of the input data
    int Compress(void *dst, unsigned int *dstSize, void *src, unsigned int srcSize);

    int CompressLZXRLE(void *dst, unsigned int *dstSize, void *src, unsigned int srcSize);

    int Decompress(void *dst, unsigned int *dstSize, void *src, unsigned int srcSize);

    int DecompressLZXRLE(void *dst, unsigned int *dstSize, void *src, unsigned int srcSize);

    int DecompressWithType(void *dst, unsigned int *dstSize, void *src, unsigned int srcSize);

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
    /// @returns `false` if there was no error, otherwise `true` (assumed, in reality it always returns `false`)
    static bool internalDecompressRle(void* dst, uint* dstSize, void* src, uint srcSize);

    static int internalCompressRle(void* dst, uint* dstSize, void* src, uint srcSize);

private:
    void *XMemCompressionContext;
    void *XMemDecompressionContext;
    nn::os::MutexType cMutex; // compression mutex
    nn::os::MutexType dcMutex; // decompression mutex
    unsigned char cData[0x40000];
    void* dcData; // devs only allocate 0x32000 for this, why?
    ECompressionTypes type;
    ECompressionTypes unk2; // set same as type initially, also compared against it. Could be something like initType or whatever.
};
