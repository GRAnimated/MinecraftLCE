#pragma once
#include "Minecraft.World/ArrayWithLength.h"
#include "TextureAtlas.h"
#include <string>

class BufferedImage;
class TexturePackRepository;
class Options;

enum _TEXTURE_NAME : unsigned int { GRASS_COLOR, FOLIAGE_COLOR };

class Textures {
public:
    Textures(TexturePackRepository*, Options*);

    void stitch();
    arrayWithLength<int> loadTexturePixels(_TEXTURE_NAME name, const std::wstring&);
    arrayWithLength<int> loadTexturePixels(BufferedImage* image);
    int loadTexture(int);
    void readImage(_TEXTURE_NAME name, const std::wstring&);
    bool IsTUImage(_TEXTURE_NAME name, const std::wstring&);

    unsigned char padding[256];
    TextureAtlas* atlas;
    TextureAtlas* atlas2;
    void* padding2;
};