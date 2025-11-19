#include "net/minecraft/client/particle/TextureUVCoordinateSet.h"

#include "net/minecraft/resources/ResourceLocation.h"

TextureUVCoordinateSet::TextureUVCoordinateSet()
    : field_0x0(1.0f), mU0(0.0), mV0(0.0), mU1(0.0), mV1(0.0), mWidth(1), mHeight(1), mTexture() {}

TextureUVCoordinateSet::TextureUVCoordinateSet(float u0, float v0, float u1, float v1,
                                               unsigned short texWidth, unsigned short texHeight,
                                               ResourceLocation tex, float param8)
    : field_0x0(param8), mU0(u0), mV0(v0), mU1(u1), mV1(v1), mWidth(texWidth), mHeight(texHeight),
      mTexture(tex) {}
