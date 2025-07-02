#include "com/mojang/blaze3d/vertex/BufferBuilder.h"
#include "com/mojang/blaze3d/vertex/Tesselator.h"
#include "net/minecraft/client/platform/NX/Platform.h"
#include "net/minecraft/client/renderer/BlockRenderer.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <cstdio>

Property* FACING;

// later fill with something actuall but without this it doesn't match as in original it doesn't use state arg
// and then it removes the state arg from being passed in final binary,
// so it shouldn't be marked as MATCHING_HACK
void BlockRenderer::renderFaceUp(const BlockState* blockState, double x, double y, double z,
                                 TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderFaceDown(const BlockState* blockState, double x, double y, double z,
                                   TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderNorth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderSouth(const BlockState* blockState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderEast(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

// NON_MATCHING
void BlockRenderer::renderWest(const BlockState* blockState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    float u0 = u;
    float v0 = v;
    float u1 = u2;
    float v1 = v2;

    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();

    if (mIsFlippedTexture) {
        std::swap(u0, u1);
    }

    if (this->_30 < 0.0f || this->_34 > 1.0f) {
        u0 = sprite->getU0(true);
        u1 = sprite->getU1(true);
    }

    if (this->_28 < 0.0f || this->_2C > 1.0f) {
        v0 = sprite->getV0(true);
        v1 = sprite->getV1(true);
    }

    if (this->dwordA4 == 1) {
        u0 = sprite->getU(this->_28 * 16.0f);
        v0 = sprite->getV(16.0f - (this->_34 * 16.0f));
        u1 = sprite->getU(this->_2C * 16.0f);
        v1 = sprite->getV(16.0f - (this->_30 * 16.0f));
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (this->dwordA4 == 2) {
        u0 = sprite->getU(16.0f - (this->_2C * 16.0f));
        v0 = sprite->getV(this->_30 * 16.0f);
        u1 = sprite->getU(16.0f - (this->_28 * 16.0f));
        v1 = sprite->getV(this->_34 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    } else if (this->dwordA4 == 3) {
        u0 = sprite->getU(16.0f - (this->_30 * 16.0f));
        u1 = sprite->getU(16.0f - (this->_34 * 16.0f));
        v0 = sprite->getV(this->_2C * 16.0f);
        v1 = sprite->getV(this->_28 * 16.0f);
        sprite->adjustUV(u0, u1);
        sprite->adjustUV(v0, v1);
    }

    int uvLockMode = this->dwordC0;
    if (uvLockMode == 3) {
        std::swap(u0, u1);
    } else if (uvLockMode == 2) {
        std::swap(u0, u1);
    } else if (uvLockMode == 1) {
        std::swap(v0, v1);
    }

    float uv1_u, uv1_v;
    float uv2_u, uv2_v;
    float uv3_u, uv3_v;
    float uv4_u, uv4_v;

    switch (this->dwordA4) {
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

    double x0 = this->_20 + x;
    double y0 = this->_28 + y;
    double y1 = this->_2C + y;
    double z0 = this->_30 + z;
    double z1 = this->_34 + z;

    builder->bucket(5);

    if (this->mIsEnableAO) {
        builder->color(mColorR_TL, mColorG_TL, mColorB_TL);
        builder->tex2(mBrightness_TL);
        builder->vertexUV(x0, y1, z1, uv1_u, uv1_v);

        builder->color(mColorR_BL, mColorG_BL, mColorB_BL);
        builder->tex2(mBrightness_BL);
        builder->vertexUV(x0, y1, z0, uv2_u, uv2_v);

        builder->color(mColorR_BR, mColorG_BR, mColorB_BR);
        builder->tex2(mBrightness_BR);
        builder->vertexUV(x0, y0, z0, uv3_u, uv3_v);

        builder->color(mColorR_TR, mColorG_TR, mColorB_TR);
        builder->tex2(mBrightness_TR);
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
        this->dwordA0 = 5;
        this->dwordA4 = 5;

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
        this->dwordA0 = 4;
        this->dwordA4 = 4;

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
        this->dword98 = 5;
        this->dword9C = 5;
        this->dwordA8 = 5;
        this->dwordAC = 4;

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
        this->dword98 = 4;
        this->dword9C = 4;
        this->dwordA8 = 4;
        this->dwordAC = 5;

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
    this->dword98 = 0;
    this->dword9C = 0;
    this->dwordA0 = 0;
    this->dwordA4 = 0;
    this->dwordA8 = 0;
    this->dwordAC = 0;
    this->dwordB4 = 0;
    this->dwordB8 = 0;
    this->dwordBC = 0;
    this->dwordC0 = 0;
    this->dwordC4 = 0;
    this->dwordC8 = 0;
}

void BlockRenderer::tesselateCrossTexture(const BlockState* state, float x, float y, float z, float unk) {
    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();
    TextureAtlasSprite* sprite = this->getTexture(state, Direction::UP);
    if (this->hasFixedTexture())
        sprite = this->mFixedTexture;

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