#pragma once

#include "java/io/File.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "nn/fs/fs_types.h"
#include "stb_image.h"

// this class is not part of Minecraft.Client nor Minecraft.World so I put it here, if you find any assert or
// anything move this
class TextureUtil {
public:
    static void ByteFlipRGBAToARGB(unsigned int& pixel);

    // non existant on Switch, symbol from WiiU
    // static int generateTextureId();
    // static void releaseTextureId(int id);
    // static void bind(int id);
    // static void prepareImage(int, int, int, int);
    // static void prepareImage(int, int, int);
    // static void anaglyph(int);
    // static void anaglyph(arrayWithLength<int>);
    // static void copyToBuffer(arrayWithLength<int>, int, int);
    // static void uploadImageChunked(int, arrayWithLength<int>, int, int, int, int, bool, bool, bool);
    // static void uploadImage(int, arrayWithLength<int>, int, int);

    static void decodeJpeg(void* buffer, int len, int* x, int* y);
    static void insertZlibAlphaChannelData(void* data, int width, int height, void* sourceData,
                                           int sourceLen);
    static int LoadTextureData(const char* fileName, int* x, int* y, int** pixels);
    static int LoadTextureData(unsigned char* data, unsigned int len, int* x, int* y, int** pixels);
};

class StbiFile {
public:
    static int read(void* user, char* data, int size);
    static void skip(void* user, int n);
    static int eof(void* user);

    static StbiFile* fromUser(void* user);

    // those 4 names are completly made-up; I don't even know if they should be part of StbiFile
    void CreateFile(const char* fileName) {
        this->m_dataRead = 0;
        this->m_fileHandle = CreateFileA(fileName, 0x80000000, 0, nullptr, 3, 0x80, 0);

        this->m_fileSize
            = this->m_fileHandle == (nn::fs::FileHandle*)-1 ? 0 : GetFileSize(this->m_fileHandle, nullptr);
    }

    void CloseFile() {
        if (this->m_fileHandle != (nn::fs::FileHandle*)-1)
            CloseHandle(this->m_fileHandle);
    }

    bool IsValidFile() { return this->m_fileHandle != (nn::fs::FileHandle*)-1; }

    StbiFile* Get() { return this; }

    nn::fs::FileHandle* m_fileHandle;
    int m_fileSize;
    int m_dataRead;
};
