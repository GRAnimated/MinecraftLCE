#pragma once

#include "types.h"
#include <string>

class BufferedImage;
class Rect2i;

class Texture {
public:
    Texture(const std::wstring&, int, int, int, int, int, int, int, BufferedImage*, bool);
    Texture(const std::wstring&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    ~Texture();
    void init(const std::wstring&, int, int, int, int, int, int, int, int, bool);
    void init(const std::wstring&, int, int, int, int, int, int, int, int, BufferedImage*, bool);
    void updateOnGPU();
    void transferFromImage(BufferedImage*);
    void getData(u32);
    void getHeight();
    void getWidth();
    static int crispBlend(int c0, int c1);
    void getManagerId();
    void bind(int);

    int m_dword0;
    unsigned int m_textureManagerId;
    int m_dword8;
    unsigned int m_width;
    unsigned int m_height;
    int m_dword14;
    int m_dword18;
    int m_dword1c;
    unsigned int m_dword20;
    unsigned int m_dword24;
    unsigned int m_dword28;
    bool m_isAnimated;
    std::wstring m_stdWstringFilename;
    Rect2i* m_textureRect;
    char m_transferred;
    char m_byte51;
    char m_byte52;
    char m_gap53;
    int m_dword54;
    void* m_qword58;
    void* m_qword60;
    void* m_qword68;
    void* m_qword70;
    void* m_qword78;
    void* m_qword80;
    void* m_qword88;
    void* m_qword90;
    void* m_qword98;
    void* m_qwordA0;
    char m_byteA8;
};

ASSERT_SIZEOF(Texture, 0xB0)
