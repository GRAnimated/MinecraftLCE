#include "net/minecraft/client/particle/TextureUVCoordinateSet.h"

#include "net/minecraft/resources/ResourceLocation.h"

TextureUVCoordinateSet::TextureUVCoordinateSet()
    : m_field0x0(1.0f), m_u0(0.0), m_v0(0.0), m_u1(0.0), m_v1(0.0), m_width(1), m_height(1), m_texture() {}

TextureUVCoordinateSet::TextureUVCoordinateSet(float u0, float v0, float u1, float v1,
                                               unsigned short texWidth, unsigned short texHeight,
                                               ResourceLocation tex, float param8)
    : m_field0x0(param8), m_u0(u0), m_v0(v0), m_u1(u1), m_v1(v1), m_width(texWidth), m_height(texHeight),
      m_texture(tex) {}
