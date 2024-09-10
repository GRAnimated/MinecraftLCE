#pragma once

#include <string>

class TextureAtlas {
public:
    void addIcon(bool, int, int, const std::wstring&);
    void addIconWithName(bool, int, int, const std::wstring&, const std::wstring&);
};
