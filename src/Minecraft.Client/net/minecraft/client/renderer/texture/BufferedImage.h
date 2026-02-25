#pragma once

class BufferedImage {
public:
    BufferedImage(int width, int height, int);
    ~BufferedImage();

    void* m_fill[96 / 8];
};
