#include "net/minecraft/client/renderer/BlockRenderer.h"

#include "NX/Platform.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/phys/AABB.h"
#include <utility>

Property* FACING;

bool BlockRenderer::hasFixedTexture() {
    return m_fixedTexture != nullptr;
}

void BlockRenderer::setLightOverride(int light) {
    m_lightOverride = light;
}

void BlockRenderer::clearLightOverride() {
    m_lightOverride = -1;
}

// name guessed
bool BlockRenderer::hasLightOverride() {
    return m_lightOverride != -1;
}

void BlockRenderer::setShape(const AABB* shape) {
    if (!m_shapeLocked) {
        m_x0 = shape->m_inX;
        m_x1 = shape->m_axX;
        m_y0 = shape->m_inY;
        m_y1 = shape->m_axY;
        m_z0 = shape->m_inZ;
        m_z1 = shape->m_axZ;
        m_partialShape
            = m_x0 > 0.0f || m_x1 < 1.0f || m_y0 > 0.0f || m_y1 < 1.0f || m_z0 > 0.0f || m_z1 < 1.0f;
    }
}

// name guessed
void BlockRenderer::renderNorth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_x0 * 16.0f);
    float u1 = sprite->getU(m_x1 * 16.0f);
    float v0 = sprite->getV(16.0f - m_y1 * 16.0f);
    float v1 = sprite->getV(16.0f - m_y0 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderNorth(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// name guessed
void BlockRenderer::renderSouth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_x0 * 16.0f);
    float u1 = sprite->getU(m_x1 * 16.0f);
    float v0 = sprite->getV(16.0f - m_y1 * 16.0f);
    float v1 = sprite->getV(16.0f - m_y0 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderSouth(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// name guessed
void BlockRenderer::renderWest(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_z0 * 16.0f);
    float u1 = sprite->getU(m_z1 * 16.0f);
    float v0 = sprite->getV(16.0f - m_y1 * 16.0f);
    float v1 = sprite->getV(16.0f - m_y0 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderWest(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// name guessed
void BlockRenderer::renderEast(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_z0 * 16.0f);
    float u1 = sprite->getU(m_z1 * 16.0f);
    float v0 = sprite->getV(16.0f - m_y1 * 16.0f);
    float v1 = sprite->getV(16.0f - m_y0 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderEast(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// name guessed
void BlockRenderer::renderFaceUp(const BlockState* blockState, double x, double y, double z,
                                 TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_x0 * 16.0f);
    float u1 = sprite->getU(m_x1 * 16.0f);
    float v0 = sprite->getV(m_z0 * 16.0f);
    float v1 = sprite->getV(m_z1 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderFaceUp(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// name guessed
void BlockRenderer::renderFaceDown(const BlockState* blockState, double x, double y, double z,
                                   TextureAtlasSprite* sprite) {
    if (hasFixedTexture())
        sprite = m_fixedTexture;

    float u0 = sprite->getU(m_x0 * 16.0f);
    float u1 = sprite->getU(m_x1 * 16.0f);
    float v0 = sprite->getV(m_z0 * 16.0f);
    float v1 = sprite->getV(m_z1 * 16.0f);
    sprite->adjustUV(u0, u1);
    sprite->adjustUV(v0, v1);
    renderFaceDown(blockState, x, y, z, sprite, u0, v0, u1, v1);
}

// NON_MATCHING | score: 7588 (lower is better)
void BlockRenderer::renderFaceUp(const BlockState* blockState, double x, double y, double z,
                                 TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_x0 < 0.0f || m_x1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_z0 < 0.0f || m_z1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dwordA8 == 1) {
        u0 = sprite->getU(m_z0 * 16.0f);
        v0 = sprite->getV(16.0f - m_x1 * 16.0f);
        u1 = sprite->getU(m_z1 * 16.0f);
        v1 = sprite->getV(16.0f - m_x0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA8 == 2) {
        u0 = sprite->getU(16.0f - m_z1 * 16.0f);
        v0 = sprite->getV(m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_z0 * 16.0f);
        v1 = sprite->getV(m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA8 == 3) {
        u0 = sprite->getU(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_x1 * 16.0f);
        v0 = sprite->getV(16.0f - m_z0 * 16.0f);
        v1 = sprite->getV(16.0f - m_z1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordC4;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dwordA8) {
    case 1:
    case 4:
        uv1_u = u1;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v1;
        break;
    case 2:
    case 5:
        uv1_u = u0;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v0;
        break;
    default:
        uv1_u = u1;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v1;
        break;
    }

    double x0 = m_x0 + x;
    double x1 = m_x1 + x;
    double y1 = m_y1 + y;
    double z0 = m_z0 + z;
    double z1 = m_z1 + z;

    builder->bucket(1);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x1, y1, z1, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x1, y1, z0, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x0, y1, z0, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x0, y1, z1, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x1, y1, z1, uv1_u, uv1_v);
        builder->vertexUV(x1, y1, z0, uv2_u, uv2_v);
        builder->vertexUV(x0, y1, z0, uv3_u, uv3_v);
        builder->vertexUV(x0, y1, z1, uv4_u, uv4_v);
    }
}

// NON_MATCHING | score: 7193 (lower is better)
void BlockRenderer::renderFaceDown(const BlockState* blockState, double x, double y, double z,
                                   TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_x0 < 0.0f || m_x1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_z0 < 0.0f || m_z1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dwordAc == 1) {
        u0 = sprite->getU(16.0f - m_z1 * 16.0f);
        v0 = sprite->getV(m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_z0 * 16.0f);
        v1 = sprite->getV(m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordAc == 2) {
        u0 = sprite->getU(m_z0 * 16.0f);
        v0 = sprite->getV(16.0f - m_x1 * 16.0f);
        u1 = sprite->getU(m_z1 * 16.0f);
        v1 = sprite->getV(16.0f - m_x0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordAc == 3) {
        u0 = sprite->getU(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_x1 * 16.0f);
        v0 = sprite->getV(16.0f - m_z0 * 16.0f);
        v1 = sprite->getV(16.0f - m_z1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordC8;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dwordAc) {
    case 1:
    case 4:
        uv1_u = u0;
        uv1_v = v0;
        uv2_u = u1;
        uv2_v = v0;
        uv3_u = u1;
        uv3_v = v1;
        uv4_u = u0;
        uv4_v = v1;
        break;
    case 2:
    case 5:
        uv1_u = u1;
        uv1_v = v1;
        uv2_u = u0;
        uv2_v = v1;
        uv3_u = u0;
        uv3_v = v0;
        uv4_u = u1;
        uv4_v = v0;
        break;
    default:
        uv1_u = u0;
        uv1_v = v1;
        uv2_u = u0;
        uv2_v = v0;
        uv3_u = u1;
        uv3_v = v0;
        uv4_u = u1;
        uv4_v = v1;
        break;
    }

    double x0 = m_x0 + x;
    double x1 = m_x1 + x;
    double y0 = m_y0 + y;
    double z0 = m_z0 + z;
    double z1 = m_z1 + z;

    builder->bucket(6);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x0, y0, z1, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x0, y0, z0, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x1, y0, z0, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x1, y0, z1, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x0, y0, z1, uv1_u, uv1_v);
        builder->vertexUV(x0, y0, z0, uv2_u, uv2_v);
        builder->vertexUV(x1, y0, z0, uv3_u, uv3_v);
        builder->vertexUV(x1, y0, z1, uv4_u, uv4_v);
    }
}

// NON_MATCHING | score: 9521 (lower is better)
void BlockRenderer::renderNorth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_isFlippedTexture) {
        std::swap(u0, u1);
    }

    if (m_x0 < 0.0f || m_x1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_y0 < 0.0f || m_y1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dword98 == 1) {
        u0 = sprite->getU(16.0f - m_y1 * 16.0f);
        v0 = sprite->getV(m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_y0 * 16.0f);
        v1 = sprite->getV(m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dword98 == 2) {
        u0 = sprite->getU(m_y0 * 16.0f);
        v0 = sprite->getV(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(m_y1 * 16.0f);
        v1 = sprite->getV(16.0f - m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dword98 == 3) {
        u0 = sprite->getU(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_x1 * 16.0f);
        v0 = sprite->getV(m_y1 * 16.0f);
        v1 = sprite->getV(m_y0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordB4;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dword98) {
    case 1:
    case 4:
        uv1_u = u1;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v1;
        break;
    case 2:
    case 5:
        uv1_u = u0;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v0;
        break;
    default:
        uv1_u = u1;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v1;
        break;
    }

    double x0 = m_x0 + x;
    double x1 = m_x1 + x;
    double y0 = m_y0 + y;
    double y1 = m_y1 + y;
    double z0 = m_z0 + z;

    builder->bucket(2);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x0, y1, z0, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x1, y1, z0, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x1, y0, z0, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x0, y0, z0, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x0, y1, z0, uv1_u, uv1_v);
        builder->vertexUV(x1, y1, z0, uv2_u, uv2_v);
        builder->vertexUV(x1, y0, z0, uv3_u, uv3_v);
        builder->vertexUV(x0, y0, z0, uv4_u, uv4_v);
    }
}

// NON_MATCHING | score: 7162 (lower is better)
void BlockRenderer::renderSouth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_isFlippedTexture) {
        std::swap(u0, u1);
    }

    if (m_x0 < 0.0f || m_x1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_y0 < 0.0f || m_y1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dword9C == 1) {
        u0 = sprite->getU(m_y0 * 16.0f);
        v1 = sprite->getV(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(m_y1 * 16.0f);
        v0 = sprite->getV(16.0f - m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dword9C == 2) {
        u0 = sprite->getU(16.0f - m_y1 * 16.0f);
        v0 = sprite->getV(m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_y0 * 16.0f);
        v1 = sprite->getV(m_x1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dword9C == 3) {
        u0 = sprite->getU(16.0f - m_x0 * 16.0f);
        u1 = sprite->getU(16.0f - m_x1 * 16.0f);
        v0 = sprite->getV(m_y1 * 16.0f);
        v1 = sprite->getV(m_y0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordB8;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dword9C) {
    case 1:
    case 4:
        uv1_u = u0;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v0;
        break;
    case 2:
    case 5:
        uv1_u = u1;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v1;
        break;
    default:
        uv1_u = u0;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v0;
        break;
    }

    double x0 = m_x0 + x;
    double x1 = m_x1 + x;
    double y0 = m_y0 + y;
    double y1 = m_y1 + y;
    double z1 = m_z1 + z;

    builder->bucket(4);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x0, y1, z1, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x0, y0, z1, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x1, y0, z1, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x1, y1, z1, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x0, y1, z1, uv1_u, uv1_v);
        builder->vertexUV(x0, y0, z1, uv2_u, uv2_v);
        builder->vertexUV(x1, y0, z1, uv3_u, uv3_v);
        builder->vertexUV(x1, y1, z1, uv4_u, uv4_v);
    }
}

// NON_MATCHING | score: 9151 (lower is better)
void BlockRenderer::renderEast(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_isFlippedTexture) {
        std::swap(u0, u1);
    }

    if (m_z0 < 0.0f || m_z1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_y0 < 0.0f || m_y1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dwordA0 == 1) {
        u0 = sprite->getU(16.0f - m_y1 * 16.0f);
        v0 = sprite->getV(m_z1 * 16.0f);
        u1 = sprite->getU(16.0f - m_y0 * 16.0f);
        v1 = sprite->getV(m_z0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA0 == 2) {
        u0 = sprite->getU(m_y0 * 16.0f);
        v0 = sprite->getV(16.0f - m_z0 * 16.0f);
        u1 = sprite->getU(m_y1 * 16.0f);
        v1 = sprite->getV(16.0f - m_z1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA0 == 3) {
        u0 = sprite->getU(16.0f - m_z0 * 16.0f);
        u1 = sprite->getU(16.0f - m_z1 * 16.0f);
        v0 = sprite->getV(m_y1 * 16.0f);
        v1 = sprite->getV(m_y0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordBc;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dwordA0) {
    case 1:
    case 4:
        uv1_u = u0;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v0;
        break;
    case 2:
    case 5:
        uv1_u = u1;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v1;
        break;
    default:
        uv1_u = u0;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v0;
        break;
    }

    double x1 = m_x1 + x;
    double y0 = m_y0 + y;
    double y1 = m_y1 + y;
    double z0 = m_z0 + z;
    double z1 = m_z1 + z;

    builder->bucket(3);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x1, y0, z1, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x1, y0, z0, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x1, y1, z0, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x1, y1, z1, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x1, y0, z1, uv1_u, uv1_v);
        builder->vertexUV(x1, y0, z0, uv2_u, uv2_v);
        builder->vertexUV(x1, y1, z0, uv3_u, uv3_v);
        builder->vertexUV(x1, y1, z1, uv4_u, uv4_v);
    }
}

// NON_MATCHING | score: 8182 (lower is better)
void BlockRenderer::renderWest(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (m_isFlippedTexture) {
        std::swap(u0, u1);
    }

    if (m_z0 < 0.0f || m_z1 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (m_y0 < 0.0f || m_y1 > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (m_dwordA4 == 1) {
        u0 = sprite->getU(m_y0 * 16.0f);
        v0 = sprite->getV(16.0f - m_z1 * 16.0f);
        u1 = sprite->getU(m_y1 * 16.0f);
        v1 = sprite->getV(16.0f - m_z0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA4 == 2) {
        u0 = sprite->getU(16.0f - m_y1 * 16.0f);
        v0 = sprite->getV(m_z0 * 16.0f);
        u1 = sprite->getU(16.0f - m_y0 * 16.0f);
        v1 = sprite->getV(m_z1 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (m_dwordA4 == 3) {
        u0 = sprite->getU(16.0f - m_z0 * 16.0f);
        u1 = sprite->getU(16.0f - m_z1 * 16.0f);
        v0 = sprite->getV(m_y1 * 16.0f);
        v1 = sprite->getV(m_y0 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = m_dwordC0;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
        std::swap(v0, v1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (m_dwordA4) {
    case 1:
    case 4:
        uv1_u = u0;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v1;
        uv3_u = u1;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v0;
        break;
    case 2:
    case 5:
        uv1_u = u1;
        uv1_v = v1;
        uv2_u = u1;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v0;
        uv4_u = u0;
        uv4_v = v1;
        break;
    default:
        uv1_u = u1;
        uv1_v = v0;
        uv2_u = u0;
        uv2_v = v0;
        uv3_u = u0;
        uv3_v = v1;
        uv4_u = u1;
        uv4_v = v1;
        break;
    }

    double x0 = m_x0 + x;
    double y0 = m_y0 + y;
    double y1 = m_y1 + y;
    double z0 = m_z0 + z;
    double z1 = m_z1 + z;

    builder->bucket(5);

    if (m_isEnableAo) {
        builder->color(m_colorRTl, m_colorGTl, m_colorBTl);
        builder->tex2(m_brightnessTl);
        builder->vertexUV(x0, y1, z1, uv1_u, uv1_v);

        builder->color(m_colorRBl, m_colorGBl, m_colorBBl);
        builder->tex2(m_brightnessBl);
        builder->vertexUV(x0, y1, z0, uv2_u, uv2_v);

        builder->color(m_colorRBr, m_colorGBr, m_colorBBr);
        builder->tex2(m_brightnessBr);
        builder->vertexUV(x0, y0, z0, uv3_u, uv3_v);

        builder->color(m_colorRTr, m_colorGTr, m_colorBTr);
        builder->tex2(m_brightnessTr);
        builder->vertexUV(x0, y0, z1, uv4_u, uv4_v);
    } else {
        builder->vertexUV(x0, y1, z1, uv1_u, uv1_v);
        builder->vertexUV(x0, y1, z0, uv2_u, uv2_v);
        builder->vertexUV(x0, y0, z0, uv3_u, uv3_v);
        builder->vertexUV(x0, y0, z1, uv4_u, uv4_v);
    }
}

void BlockRenderer::tesselateEndRodCenter(const BlockState* state, float x, float y, float z) {
    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();
    this->setShape(Blocks::END_ROD->getShapeRod(state));

    TextureAtlasSprite* sprite = this->getTexture(state, Direction::DOWN);
    float startRodU, startRodV;
    float endRodU, endRodV;
    startRodU = sprite->getU(0.0);
    startRodV = sprite->getV(0.0);
    endRodU = sprite->getU(2.0);
    endRodV = sprite->getV(15.0);
    sprite->adjustUV(startRodU, endRodU);
    sprite->adjustUV(startRodV, endRodV);

    float startTopRodU, startTopRodV;
    float endTopRodU, endTopRodV;
    startTopRodU = sprite->getU(2.0);
    startTopRodV = sprite->getV(0.0);
    endTopRodU = sprite->getU(4.0);
    endTopRodV = sprite->getV(2.0);
    sprite->adjustUV(startTopRodU, endTopRodU);
    sprite->adjustUV(startTopRodV, endTopRodV);

    float startTopRodU2, startTopRodV2;
    float endTopRodU2, endTopRodV2;
    startTopRodU2 = sprite->getU(4.0);
    startTopRodV2 = sprite->getV(2.0);
    endTopRodU2 = sprite->getU(2.0);
    endTopRodV2 = sprite->getV(0.0);
    sprite->adjustUV(startTopRodU2, endTopRodU2);
    sprite->adjustUV(startTopRodV2, endTopRodV2);

    switch (state->getValue<Direction*>(FACING)->get3DDataValue()) {
    case 0: {
        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, startTopRodU2, startTopRodV2, endTopRodU2, endTopRodV2);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);
        this->renderSouth(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);
        this->renderWest(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);
        break;
    }
    case 2: {
        this->m_dwordA0 = 5;
        this->m_dwordA4 = 5;

        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);
        this->renderSouth(state, x, y, z, sprite, startTopRodU2, startTopRodV2, endTopRodU2, endTopRodV2);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderWest(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        break;
    }
    case 3: {
        this->m_dwordA0 = 4;
        this->m_dwordA4 = 4;

        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, endRodU, endRodV, startRodU, startRodV);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);
        this->renderSouth(state, x, y, z, sprite, endTopRodU2, endTopRodV2, startTopRodU2, startTopRodV2);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderWest(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        break;
    }
    case 4: {
        this->m_dword98 = 5;
        this->m_dword9C = 5;
        this->m_dwordA8 = 5;
        this->m_dwordAc = 4;

        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderSouth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);
        this->renderWest(state, x, y, z, sprite, endTopRodU2, endTopRodV2, startTopRodU2, startTopRodV2);
        break;
    }
    case 5: {
        this->m_dword98 = 4;
        this->m_dword9C = 4;
        this->m_dwordA8 = 4;
        this->m_dwordAc = 5;

        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderSouth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);
        this->renderWest(state, x, y, z, sprite, startTopRodU2, startTopRodV2, endTopRodU2, endTopRodV2);
        break;
    }
    default: {
        builder->color(1.0f, 1.0f, 1.0f, 1.0f);
        this->renderFaceUp(state, x, y, z, sprite, startTopRodU, startTopRodV, endTopRodU, endTopRodV);

        builder->color(0.5f, 0.5f, 0.5f, 1.0f);
        this->renderFaceDown(state, x, y, z, sprite, startTopRodU2, startTopRodV2, endTopRodU2, endTopRodV2);

        builder->color(0.8f, 0.8f, 0.8f, 1.0f);
        this->renderNorth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderSouth(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        builder->color(0.6f, 0.6f, 0.6f, 1.0f);
        this->renderEast(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);
        this->renderWest(state, x, y, z, sprite, startRodU, startRodV, endRodU, endRodV);

        break;
    }
    }
    this->m_dword98 = 0;
    this->m_dword9C = 0;
    this->m_dwordA0 = 0;
    this->m_dwordA4 = 0;
    this->m_dwordA8 = 0;
    this->m_dwordAc = 0;
    this->m_dwordB4 = 0;
    this->m_dwordB8 = 0;
    this->m_dwordBc = 0;
    this->m_dwordC0 = 0;
    this->m_dwordC4 = 0;
    this->m_dwordC8 = 0;
}

void BlockRenderer::tesselateCrossTexture(const BlockState* state, float x, float y, float z, float unk) {
    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();
    TextureAtlasSprite* sprite = this->getTexture(state, Direction::UP);
    if (this->hasFixedTexture())
        sprite = this->m_fixedTexture;

    float U0 = sprite->getU0(1.0f);
    float V0 = sprite->getV0(1.0f);
    float U1 = sprite->getU1(1.0f);
    float V1 = sprite->getV1(1.0f);

    float test = unk * 0.45;
    float v20 = (x + 0.5) - test;
    float v21 = (x + 0.5) + test;
    float v25 = (z + 0.5) - test;
    float v24 = (z + 0.5) + test;

    builder->vertexUV(v20, y + unk, v25, U0, V0);
    builder->vertexUV(v20, y + 0.0, v25, U0, V1);
    builder->vertexUV(v21, y + 0.0, v24, U1, V1);
    builder->vertexUV(v21, y + unk, v24, U1, V0);
    builder->vertexUV(v21, y + unk, v24, U0, V0);
    builder->vertexUV(v21, y + 0.0, v24, U0, V1);
    builder->vertexUV(v20, y + 0.0, v25, U1, V1);
    builder->vertexUV(v20, y + unk, v25, U1, V0);
    builder->vertexUV(v20, y + unk, v24, U0, V0);
    builder->vertexUV(v20, y + 0.0, v24, U0, V1);
    builder->vertexUV(v21, y + 0.0, v25, U1, V1);
    builder->vertexUV(v21, y + unk, v25, U1, V0);
    builder->vertexUV(v21, y + unk, v25, U0, V0);
    builder->vertexUV(v21, y + 0.0, v25, U0, V1);
    builder->vertexUV(v20, y + 0.0, v24, U1, V1);
    builder->vertexUV(v20, y + unk, v24, U1, V0);
}
