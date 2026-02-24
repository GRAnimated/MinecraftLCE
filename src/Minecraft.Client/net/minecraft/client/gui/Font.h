#pragma once

#include <string>

class Options;
class Textures;
class ResourceLocation;
class BufferBuilder;
class Random;

class Font {
public:
    static ResourceLocation sDefaultFontRsrc;
    static ResourceLocation sAlternateFontRsrc;
    static unsigned short sDefaultText[644];

    Font(Options*, const std::wstring&, Textures*, bool, ResourceLocation*, int, int, int, int,
         unsigned short* renderList);
    void cacheCharacter(int);
    void renderCharacter(wchar_t, BufferBuilder*);
    void drawShadow(const std::wstring&, int, int, int);
    void draw(const std::wstring&, int, int, int, bool, bool);
    void draw(const std::wstring& text, int x, int y, int colour);
    std::wstring sanitize(const std::wstring&, bool);
    int width(const std::wstring&);

    void* m_font0;
    void* m_cachedCharacters;
    char m_gap10[8];
    Random* m_random;
    char m_gap20[128];
    Textures* m_textures;
    void* m_qwordA8;
    uint16_t m_wordB0;
    int m_horizontalCharsCount;
    int m_verticalCharsCount;
    int m_charWidth;
    int m_charHeight;
    ResourceLocation* m_fontTextureResourceLoc;
    char m_filler[22];
};
