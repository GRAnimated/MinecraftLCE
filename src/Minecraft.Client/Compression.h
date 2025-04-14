#pragma once

class Compression {
public:
    static void CreateNewThreadStorage();
    static void ReleaseThreadStorage();

    /// @brief Decompresses "Vita RLE"
    /// @param out Output buffer to store decompressed data
    /// @param sizeOut Pointer to uint to store the size of the decompressed data
    /// @param in Pointer to the input compressed data
    /// @param sizeIn The size of the input data
    static void VitaVirtualDecompress(void* dst, uint* dstSize, void* src, uint srcSize);

    /// @brief Decompresses Internal RLE, mainly used for chunks.
    /// @param out Output buffer to store decompressed data
    /// @param sizeOut Pointer to uint to store the size of the decompressed data
    /// @param in Pointer to the input compressed data
    /// @param sizeIn The size of the input data
    /// @returns `false` if there was no error, otherwise `true` (assumed, in reality it always returns `false`)
    static bool internalDecompressRle(void* dst, uint* dstSize, void* src, uint srcSize);
};
