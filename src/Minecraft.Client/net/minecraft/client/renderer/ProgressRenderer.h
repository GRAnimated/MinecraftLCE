#pragma once

class Minecraft;

class ProgressRenderer {
public:
    ProgressRenderer(Minecraft* mc);

    unsigned char m_padding[0x60];
};
