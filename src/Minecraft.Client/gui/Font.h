#pragma once
#include <string>

class Options;
class Textures;
class ResourceLocation;
class BufferBuilder;

class Font {
public:
    Font(Options*, const std::wstring&, Textures*, bool, ResourceLocation*, int, int, int, int, unsigned short*);
    void cacheCharacter(int);
    void renderCharacter(wchar_t, BufferBuilder*);
    void drawShadow(const std::wstring&, int, int, int);
    void draw(const std::wstring&, int, int, int, bool, bool);
    std::wstring sanitize(const std::wstring&, bool);
    int width(const std::wstring&);
};
