#pragma once

class Minecraft;
class Textures;

class LevelRenderer {
    public:
    LevelRenderer(Minecraft *mc, Textures *textures);

    unsigned char padding[0x378];
};