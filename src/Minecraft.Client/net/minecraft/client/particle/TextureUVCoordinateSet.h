#pragma once

#include "net/minecraft/resources/ResourceLocation.h"

class TextureUVCoordinateSet {
public:
    TextureUVCoordinateSet();
    TextureUVCoordinateSet(float, float, float, float, unsigned short, unsigned short, ResourceLocation,
                           float);

    float field_0x0;
    float mU0;
    float mV0;
    float mU1;
    float mV1;
    unsigned short mWidth;
    unsigned short mHeight;
    ResourceLocation mTexture;
};
