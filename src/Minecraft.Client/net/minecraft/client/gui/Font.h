#pragma once

#include <string>

class Options;
class Textures;
class ResourceLocation;
class BufferBuilder;

class Font {
public:
    Font(Options*, const std::wstring&, Textures*, bool, ResourceLocation*, int, int, int, int,
         unsigned short* renderList);
    void cacheCharacter(int);
    void renderCharacter(wchar_t, BufferBuilder*);
    void drawShadow(const std::wstring&, int, int, int);
    void draw(const std::wstring&, int, int, int, bool, bool);
    void draw(const std::wstring& text, int x, int y, int colour);
    std::wstring sanitize(const std::wstring&, bool);
    int width(const std::wstring&);

    static ResourceLocation sDefaultFontRsrc;
    static ResourceLocation sAlternateFontRsrc;
    unsigned char padding[0xE8];
    static unsigned short sDefaultText[644];
};
