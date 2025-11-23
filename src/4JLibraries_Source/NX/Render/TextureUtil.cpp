#include "NX/Render/TextureUtil.h"

#include "DecompUtils.h"
#include "java/io/File.h"
#include "zlib.h"
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"

void TextureUtil::ByteFlipRGBAToARGB(unsigned int& pixel) {
    pixel = (pixel & 0xFF00FF00) | (pixel & 0x000000FF) << 16 | (pixel & 0x00FF0000) >> 16;
}

void TextureUtil::decodeJpeg(void* buffer, int len, int* x, int* y) {
    int _x, _y, channelsCount;
    if (stbi_load_from_memory((const stbi_uc*)buffer, len, &_x, &_y, &channelsCount, 4)) {
        *x = _x;
        *y = _y;
    }
}

// NON_MATCHING: I don't understand the graphic shit too much so this is shitty impl
void TextureUtil::insertZlibAlphaChannelData(void* data, int width, int height, void* sourceData,
                                             int sourceLen) {
    unsigned long decompressedSize = width * height;
    unsigned char* alphaData = new unsigned char[decompressedSize];

    bool success = false;

    if (!uncompress(alphaData, &decompressedSize, (unsigned char*)sourceData, sourceLen)) {
        if (width > 0 && height > 0)
            success = true;
    }

    if (success) {
        unsigned char* currentAlphaPixel = alphaData;
        unsigned char* currentColorRow = (unsigned char*)data;

        for (int y = 0; y < height; ++y) {
            unsigned char* currentColorPixel = currentColorRow;

            for (int x = 0; x < width; ++x) {
                unsigned char alphaValue = *currentAlphaPixel;

                float alphaFactor = (float)alphaValue / 255.0f;

                float blue = (float)currentColorPixel[0];
                float green = (float)currentColorPixel[1];
                float red = (float)currentColorPixel[2];

                currentColorPixel[0] = (unsigned char)decomp_fminf(blue / alphaFactor, 255.0f);
                currentColorPixel[1] = (unsigned char)decomp_fminf(green / alphaFactor, 255.0f);
                currentColorPixel[2] = (unsigned char)decomp_fminf(red / alphaFactor, 255.0f);

                currentColorPixel[3] = alphaValue;

                currentColorPixel += 4;
                currentAlphaPixel++;
            }
            currentColorRow += width;
        }
    }

    delete[] alphaData;
}

int ProcessLoadedTextureData(unsigned char* data, int* x, int* y, int** pixels) {
    if (!data)
        return -1;
    size_t size = (*x) * (*y) * 4;
    unsigned int* ptr = (unsigned int*)malloc(size);

    *pixels = (int*)ptr;
    memcpy(ptr, data, size);

    stbi_image_free(data);

    if ((*x) * (*y) >= 1) {
        unsigned int* pixel = (unsigned int*)*pixels;
        for (int i = 0; i < (*x) * (*y); i++) {
            TextureUtil::ByteFlipRGBAToARGB(*(pixel++));
        }
    }
    return 0;
}

static stbi_io_callbacks sCallbacks;
int TextureUtil::LoadTextureData(const char* fileName, int* x, int* y, int** pixels) {
    sCallbacks.read = StbiFile::read;
    sCallbacks.skip = StbiFile::skip;
    sCallbacks.eof = StbiFile::eof;

    StbiFile file;
    file.CreateFile(fileName);

    int result;
    if (file.IsValidFile()) {
        int channels = 0;
        unsigned char* data = stbi_load_from_callbacks(&sCallbacks, file.Get(), x, y, &channels, 4);
        result = ProcessLoadedTextureData(data, x, y, pixels);
    } else {
        result = -1;
    }

    file.CloseFile();
    return result;
}

int TextureUtil::LoadTextureData(unsigned char* data, unsigned int len, int* x, int* y, int** pixels) {
    int channels = 0;
    unsigned char* stbi_data = stbi_load_from_memory(data, len, x, y, &channels, 4);
    return ProcessLoadedTextureData(stbi_data, x, y, pixels);
}

int StbiFile::read(void* user, char* data, int size) {
    unsigned int dataRead = 0;
    StbiFile* file = StbiFile::fromUser(user);
    if ((ReadFile(file->mFileHandle, data, size, &dataRead, nullptr) & 0x80000000) != 0) {
        return -1;
    }
    file->mDataRead += dataRead;
    return dataRead;
}

// this one requires nn sdk symbol which I wont't bother to get
// void StbiFile::skip(void* user, int n) {}

// NON_MATCHING: some weird stuff is going on here, but logic should be the same though
int StbiFile::eof(void* user) {
    return StbiFile::fromUser(user)->mFileSize <= StbiFile::fromUser(user)->mDataRead;
}
