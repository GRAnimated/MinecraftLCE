#include "Minecraft.Client/platform/NX/Platform.h"
#include "Minecraft.Client/renderer/BlockRenderer.h"
#include "Minecraft.Client/renderer/BufferBuilder.h"
#include "Minecraft.Client/renderer/Tesselator.h"
#include "Minecraft.Client/renderer/texture/TextureAtlasSprite.h"
#include "Minecraft.World/level/block/Blocks.h"
#include "Minecraft.World/level/block/EndRodBlock.h"
#include "Minecraft.World/level/block/state/AbstractProperty.h"
#include "Minecraft.Core/Direction.h"
#include <cstdio>

Property* FACING;

// later fill with something actuall but without this it doesn't match as in original it doesn't use state arg
// and then it removes the state arg from being passed in final binary,
// so it shouldn't be marked as MATCHING_HACK
void BlockRenderer::renderFaceUp(BlockState const* pState, double x, double y, double z,
                                 TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderFaceDown(BlockState const* pState, double x, double y, double z,
                                   TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderNorth(BlockState const* pState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderSouth(BlockState const* pState, double x, double y, double z,
                                TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderEast(BlockState const* pState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::renderWest(BlockState const* pState, double x, double y, double z,
                               TextureAtlasSprite* sprite, float u, float v, float u2, float v2) {
    printf("", this, x, y, z, sprite, u, v, u2, v2);
}

void BlockRenderer::tesselateEndRodCenter(BlockState const* state, float x, float y, float z) {
    BufferBuilder* builder = Tesselator::getInstance()->getBuilder();
    this->setShape(((EndRodBlock*)Blocks::END_ROD)->getShapeRod(state));

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