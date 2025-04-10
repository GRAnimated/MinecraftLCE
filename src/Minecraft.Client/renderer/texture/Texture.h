#pragma once

#include "types.h"
#include <string>

class BufferedImage;
class Rect2i;

class Texture {
public:
    Texture(std::wstring const&, int, int, int, int, int, int, int, BufferedImage*, bool);
    Texture(std::wstring const&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    ~Texture();
    void init(std::wstring const&, int, int, int, int, int, int, int, int, bool);
    void init(std::wstring const&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    void updateOnGPU();
    void transferFromImage(BufferedImage*);
    void getData(u32);
    void getHeight();
    void getWidth();
    static void crispBlend(int, int);
    void getManagerId();
    void bind(int);

    int dword_0;
    unsigned int mTextureManagerId;
    int dword_8;
    unsigned int mWidth;
    unsigned int mHeight;
    int dword_14;
    int dword_18;
    int dword_1c;
    unsigned int dword_20;
    unsigned int dword_24;
    unsigned int dword_28;
    bool mIsAnimated;
    std::wstring std_wstring_filename;
    Rect2i* mTextureRect;
    char mTransferred;
    char byte_51;
    char byte_52;
    char gap_53;
    int dword_54;
    void* qword_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    void* qword_78;
    void* qword_80;
    void* qword_88;
    void* qword_90;
    void* qword_98;
    void* qword_a0;
    char byte_a8;
};

ASSERT_SIZEOF(Texture, 0xB0)