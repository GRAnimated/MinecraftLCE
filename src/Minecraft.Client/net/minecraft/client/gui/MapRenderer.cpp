#include "net/minecraft/client/gui/MapRenderer.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"

#include "NX/Render/C4JRender.h"
#include "com/mojang/blaze3d/platform/GlStateManager.h"
#include "com/mojang/blaze3d/vertex/BufferBuilder.h"
#include "com/mojang/blaze3d/vertex/Tesselator.h"

#include "net/minecraft/client/gui/Font.h"
#include "net/minecraft/client/renderer/texture/BufferedImage.h"
#include "net/minecraft/client/renderer/texture/Textures.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/level/saveddata/MapItemSavedData.h"
#include "net/minecraft/world/level/saveddata/maps/MapDecoration.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

bool MapRenderer::sColoursNeedReload = true;

MapRenderer::MapInstance::MapInstance(MapRenderer* holder, const std::shared_ptr<MapItemSavedData>& savedData)
    : mMapRenderer(holder), mSavedData(savedData) {
    this->mMapPixels = arrayWithLength<int>(0x4000LL, true);
    for (int i = 0; i != 0x4000; i++) {
        this->mMapPixels[i] = 0;
    }
    if (MapRenderer::sColoursNeedReload)
        MapRenderer::reloadColours();
}

void MapRenderer::MapInstance::fjUpdateWithRenderContext() {
    if (this->mMapTextureId == -1) {
        BufferedImage image(128, 128, 0);
        this->mMapTextureId
            = this->mMapRenderer->mTextures->getTexture(&image, (C4JRender::eTextureFormat)0, 0);
        this->mCreatedTexture = true;
    }

    if (this->mCreatedTexture)
        this->mMapRenderer->mTextures->replaceTextureDirect(this->mMapPixels, 128, 128, this->mMapTextureId);
}

bool sortByTexture(const MapDecoration& a, const MapDecoration& b) {
    return (a.getImg() < 0x10) & (b.getImg() > 0xF);  // generates warning but matches
}

// NON_MATCHING: stack issues, also don't know how to replicate that map destruction being earlier
void MapRenderer::MapInstance::draw(const std::shared_ptr<Player>& _player) {
    this->fjUpdateWithRenderContext();
    Player* player = _player.get();  // why?

    Tesselator* tesselator = Tesselator::getInstance();
    BufferBuilder* bufferBuilder = tesselator->getBuilder();
    GlStateManager::bindTexture(this->mMapTextureId);
    GlStateManager::enableBlend();
    GlStateManager::blendFunc(2, 6);
    GlStateManager::disableAlphaTest();
    bufferBuilder->begin();
    bufferBuilder->vertexUV(0.0f, 128.0f, -0.02f, 0.0f, 1.0f);
    bufferBuilder->vertexUV(128.0f, 128.0f, -0.02f, 1.0f, 1.0f);
    bufferBuilder->vertexUV(128.0f, 0.0f, -0.02f, 1.0f, 0.0f);
    bufferBuilder->vertexUV(0.0f, 0.0f, -0.02f, 0.0f, 0.0f);
    tesselator->end();
    GlStateManager::enableAlphaTest();
    GlStateManager::disableBlend();

    std::vector<MapDecoration> decorations = this->mSavedData->fjGetAllDecorations();
    std::sort(decorations.begin(), decorations.end(), sortByTexture);

    {
        std::unordered_map<int, int> map;

        unsigned int a = 0;
        int lastDecorTexId = -1;  // do this as decor imgs are split to two
        float b = -0.04f;

        for (const auto& decor : decorations) {
            if ((player || decor.renderOnFrame()) && decor.isIdk()
                && (!player || decor.getType() != &MapDecoration::Type::MANSION)) {
                byte img = decor.getImg();
                int hashCode = decor.hashCode();
                if (map.find(hashCode) == map.end() || map.at(hashCode) <= 2) {
                    int tempTexId = img > 15 ? 120 : 14;
                    if (lastDecorTexId != tempTexId) {
                        this->mMapRenderer->mTextures->bind(
                            this->mMapRenderer->mTextures->loadTexture(tempTexId));

                        lastDecorTexId = tempTexId;
                    }

                    GlStateManager::pushMatrix();
                    GlStateManager::translatef(0.0f + decor.getX() / 2.0f + 64.0f,
                                               0.0f + decor.getY() / 2.0f + 64.0f, b);
                    GlStateManager::rotatef((decor.getRot() * 360) / 16.0f, 0.0f, 0.0f, 1.0f);
                    GlStateManager::scalef(4.0f, 4.0f, 3.0f);
                    GlStateManager::translatef(-0.125F, 0.125F, 0.0f);
                    float u = (float)(img % 4 + 0) / 4.0f;
                    float v = (float)(img / 4 + 0) / 4.0f;
                    float u1 = (float)(img % 4 + 1) / 4.0f;
                    float v1 = (float)(img / 4 + 1) / 4.0f;
                    bufferBuilder->begin();
                    bufferBuilder->vertexUV(-1.0, 1.0, a * -0.001f, u, v);
                    bufferBuilder->vertexUV(1.0, 1.0, a * -0.001f, u1, v);
                    bufferBuilder->vertexUV(1.0, -1.0, a * -0.001f, u1, v1);
                    bufferBuilder->vertexUV(-1.0, -1.0, a * -0.001f, u, v1);
                    tesselator->end();
                    GlStateManager::popMatrix();

                    ++a;
                    map[hashCode]++;
                    b -= 0.01f;
                }
            }
        }
    }

    {
        Player* player_ = _player.get();
        GlStateManager::pushMatrix();
        GlStateManager::translatef(0.0f, 0.0f, -0.06f);
        GlStateManager::scalef(1.0f, 1.0f, 1.0f);

        if (_player) {
            int x = floor(_player->mX);
            int y = floor(_player->mY + _player->getEyeHeight());
            int z = floor(_player->mZ);
            std::wstring cords = formatwstr(L"X: %d, Y: %d, Z: %d", x, y, z);
            this->mMapRenderer->mFont->draw(cords, 0, 0,
                                            Minecraft::GetInstance()->getColourTable()->getColour(Map_Text));
        }

        GlStateManager::popMatrix();
    }
}

MapRenderer::MapRenderer(Font* font, Options* options, Textures* textures) {
    this->mTextures = textures;
    this->mOptions = options;
    this->mFont = font;
}

MapRenderer::MapInstance* MapRenderer::getMapInstance(const std::shared_ptr<MapItemSavedData>& savedData) {
    auto map = this->mMaps.find(savedData->mPath);
    if (map == this->mMaps.end()) {
        this->mMaps[savedData->mPath] = new MapInstance(this, savedData);
        map = this->mMaps.find(savedData->mPath);
    }

    return map->second;
}

void MapRenderer::render(const std::shared_ptr<MapItemSavedData>& savedData,
                         const std::shared_ptr<Player>& player) {
    this->getMapInstance(savedData)->draw(player);
}

void MapRenderer::reloadColours() {
    ColourTable* colourTable = Minecraft::GetInstance()->getColourTable();

    for (int i = 0; i < 208; i++) {
        int finalColor;
        if (i / 4 == 0) {
            finalColor = (8 * ((i + i / 128) & 1)) | 0x10;
        } else {
            int baseColor = colourTable->getColour(MaterialColor::MATERIAL_COLORS[i / 4]->mColor);

            int brightness = 220;

            if ((i & 3) == 2) {
                brightness = 255;
            }

            if ((i & 3) == 0) {
                brightness = 180;
            }

            int r = (baseColor >> 16 & 0xFF) * brightness / 255;
            int g = (baseColor >> 8 & 0xFF) * brightness / 255;
            int b = (baseColor & 0xFF) * brightness / 255;

            finalColor = (0xFF << 24) | (b << 16) | (g << 8) | r;
        }

        sMaterialColorPalette[i] = finalColor;
    }

    sColoursNeedReload = false;
}
