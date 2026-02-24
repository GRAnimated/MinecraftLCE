#pragma once

#include "net/minecraft/resources/ResourceLocation.h"

class TextureUVCoordinateSet {
public:
    TextureUVCoordinateSet();
    TextureUVCoordinateSet(const TextureUVCoordinateSet*);
    TextureUVCoordinateSet(float, float, float, float, unsigned short, unsigned short, ResourceLocation,
                           float);

    static TextureUVCoordinateSet* fromOldSystem(int);
    float m_field0x0;
    float m_u0;
    float m_v0;
    float m_u1;
    float m_v1;
    unsigned short m_width;
    unsigned short m_height;
    ResourceLocation m_texture;
};
