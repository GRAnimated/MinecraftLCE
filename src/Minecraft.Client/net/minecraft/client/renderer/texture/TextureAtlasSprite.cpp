#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"

void TextureAtlasSprite::initUVs(float u0, float v0, float u1, float v1) {
    m_u0 = u0;
    m_u1 = u1;
    m_v0 = v0;
    m_v1 = v1;
}

int TextureAtlasSprite::getX() const {
    return m_x;
}

int TextureAtlasSprite::getY() const {
    return m_y;
}

int TextureAtlasSprite::getWidth() const {
    return m_width;
}

int TextureAtlasSprite::getHeight() const {
    return m_height;
}

float TextureAtlasSprite::getU0(bool inset) const {
    return inset ? m_u0 + 1.0f / 4096.0f : m_u0;
}

float TextureAtlasSprite::getU1(bool inset) const {
    return inset ? m_u1 - 1.0f / 4096.0f : m_u1;
}

float TextureAtlasSprite::getU(double pixel) const {
    float end = getU1(false);
    float span = end - getU0(false);
    float base = getU0(false);
    return (float)pixel * 0.0625f * span + base;
}

float TextureAtlasSprite::getV0(bool inset) const {
    return inset ? m_v0 + 1.0f / 4096.0f : m_v0;
}

float TextureAtlasSprite::getV1(bool inset) const {
    return inset ? m_v1 - 1.0f / 4096.0f : m_v1;
}

float TextureAtlasSprite::getV(double pixel) const {
    float end = getV1(false);
    float span = end - getV0(false);
    float base = getV0(false);
    return (float)pixel * 0.0625f * span + base;
}

void TextureAtlasSprite::adjustUV(float& start, float& end) {
    float* lower = &start;
    float* upper = &end;
    if (start < end) {
    } else if (start > end) {
        lower = &end;
        upper = &start;
    } else {
        return;
    }
    *lower += 1.0f / 4096.0f;
    *upper -= 1.0f / 4096.0f;
}
