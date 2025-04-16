#pragma once

class Minecraft;

class ProgressRenderer {
    public:
    ProgressRenderer(Minecraft *mc);

    unsigned char padding[0x60];
};