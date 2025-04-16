#pragma once
// maybe Texture should also be here?
#include <string>
#include "Minecraft.World/ArrayWithLength.h"

class BufferedImage;
class TexturePackRepository;
class Options;

enum _TEXTURE_NAME : unsigned int {
    GRASS_COLOR,
    FOLIAGE_COLOR
};

class Textures {
    public:
    Textures(TexturePackRepository *, Options *);

    arrayWithLength<int> loadTexturePixels(_TEXTURE_NAME name, const std::wstring&);
    arrayWithLength<int> loadTexturePixels(BufferedImage *image);
    void readImage(_TEXTURE_NAME name, const std::wstring&);
    bool IsTUImage(_TEXTURE_NAME name, const std::wstring&);
};