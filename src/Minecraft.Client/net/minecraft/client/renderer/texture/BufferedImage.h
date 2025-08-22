#pragma once

class BufferedImage {
public:
    BufferedImage(int width, int height, int);
    ~BufferedImage();

    void* fill[96 / 8];
};
