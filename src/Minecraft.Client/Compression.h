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
    static void VitaVirtualDecompress(void* out, uint* sizeOut, void* in, uint sizeIn);
};
