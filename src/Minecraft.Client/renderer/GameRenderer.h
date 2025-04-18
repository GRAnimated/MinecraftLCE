#pragma once

#include <string>

class Font;
class ResourceManager;
class Minecraft;

class GameRenderer {
    // meant to be public?
    static void renderNameTagInWorld(Font*, std::wstring const&, float, float, float, int, float, float, bool,
                                     bool, int, float);

public:
    GameRenderer(Minecraft* mc, ResourceManager* rsrcManager);

    unsigned char padding[0x2290];
};