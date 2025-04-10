#pragma once

#include <string>

class Font;

class GameRenderer {
    static void renderNameTagInWorld(Font*, std::wstring const&, float, float, float, int, float, float, bool,
                                     bool, int, float);
};