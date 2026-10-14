#pragma once

#include "net/minecraft/world/level/material/MaterialColor.h"
#include <string>
#include <unordered_map>

class ColourTable {
public:
    ColourTable(unsigned char*, unsigned int);
    ColourTable(const ColourTable&, unsigned char*, unsigned int);
    static void staticCtor();
    unsigned int getColour(eMinecraftColour);
    void read(unsigned char*, unsigned int);
    void setColour(const std::wstring&, unsigned int);

    static constexpr unsigned int COLOUR_COUNT = 486;
    unsigned int m_colours[COLOUR_COUNT];

private:
    static const wchar_t* const s_colourNames[COLOUR_COUNT];
    static std::unordered_map<std::wstring, int> s_nameToColour;
};

static_assert(sizeof(ColourTable) == 0x798, "Original colour table contains 486 words");
