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

    void* font0;
    void* mCachedCharacters;
    char gap10[8];
    Random* mRandom;
    char gap20[128];
    Textures* mTextures;
    void* qwordA8;
    uint16_t wordB0;
    int mHorizontalCharsCount;
    int mVerticalCharsCount;
    int mCharWidth;
    int mCharHeight;
    ResourceLocation* mFontTextureResourceLoc;
    char filler[22];
};
