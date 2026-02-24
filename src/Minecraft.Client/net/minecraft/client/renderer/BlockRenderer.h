#pragma once

#include "net/minecraft/world/level/storage/LevelSource.h"

class TextureAtlasSprite;
class AABB;

class BlockRenderer {
public:
    BlockRenderer(LevelSource*, int, int, int, unsigned char*);
    ~BlockRenderer();

    void setLightOverride(int);
    bool tesselateInWorld(const BlockState*, const BlockPos&, const BlockState*,
                          std::shared_ptr<BlockEntity>);
    void tesselateInWorldFixedTexture(const BlockState*, const BlockPos&, TextureAtlasSprite*);
    void clearLightOverride();
    void setShape(const AABB*);
    void renderFaceUp(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                      float);
    void renderFaceDown(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                        float);
    void renderNorth(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                     float);
    void renderSouth(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                     float);
    void renderEast(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                    float);
    void renderWest(const BlockState*, double, double, double, TextureAtlasSprite*, float, float, float,
                    float);

    TextureAtlasSprite* getTexture(const BlockState*, const Direction*);
    bool hasFixedTexture();

    void tesselateEndRodCenter(const BlockState*, float, float, float);
    void tesselateCrossTexture(const BlockState*, float, float, float, float);

    char m_gap0[8];
    LevelSource* m_source;
    TextureAtlasSprite* m_fixedTexture;
    char m_gap18[4];
    bool m_isFlippedTexture;
    bool m_isCullFaceDown;
    bool m_isFancyLighting;
    bool m_1f;
    float m_20;
    float m_24;
    float m_28;
    float m_2C;
    float m_30;
    float m_34;
    char m_gap38[94];
    int m_dword98;
    int m_dword9C;
    int m_dwordA0;
    int m_dwordA4;
    int m_dwordA8;
    int m_dwordAc;
    int m_dwordB0;
    int m_dwordB4;
    int m_dwordB8;
    int m_dwordBc;
    int m_dwordC0;
    int m_dwordC4;
    int m_dwordC8;
    bool m_isEnableAo;
    void* m_qwordD0;
    char m_unk[152];
    int m_brightnessTl, m_brightnessBl, m_brightnessBr, m_brightnessTr;
    float m_colorRTl, m_colorRBl, m_colorRBr, m_colorRTr;
    float m_colorGTl, m_colorGBl, m_colorGBr, m_colorGTr;
    float m_colorBTl, m_colorBBl, m_colorBBr, m_colorBTr;
};
