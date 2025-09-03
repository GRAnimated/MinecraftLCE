#include "net/minecraft/client/gui/GuiComponent.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/gui/Gui.h"

#include "net/minecraft/client/gui/Font.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include <cmath>

GuiComponent::GuiComponent() {}

void GuiComponent::fill(int x1, int y1, int x2, int y2, int color) {
    int temp;

    if (x1 < x2) {
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y1 < y2) {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    float alpha = (color >> 24 & 0xFF) / 255.0f;
    float red = (color >> 16 & 0xFF) / 255.0f;
    float green = (color >> 8 & 0xFF) / 255.0f;
    float blue = (color & 0xFF) / 255.0f;

    Tesselator* tesselator = Tesselator::getInstance();
    BufferBuilder* builder = tesselator->getBuilder();

    GlStateManager::enableBlend();
    GlStateManager::disableTexture();
    GlStateManager::blendFunc(5u, 6u);
    GlStateManager::color4f(red, green, blue, alpha);

    builder->begin();
    builder->vertex(x1, y2, 0.0f);
    builder->vertex(x2, y2, 0.0f);
    builder->vertex(x2, y1, 0.0f);
    builder->vertex(x1, y1, 0.0f);
    builder->end();

    GlStateManager::enableTexture();
    GlStateManager::disableBlend();
}

void GuiComponent::drawString(Font* font, const std::wstring& str, int a4, int a5, int a6) {
    font->drawShadow(str, a4, a5, a6);
}

void GuiComponent::drawCenteredString(Font* font, const std::wstring& str, int a4, int a5, int a6) {
    font->drawShadow(str, a4 - font->width(str) / 2, a5, a6);
}

void GuiComponent::fillGradient(int a2, int a3, int a4, int a5, int a6, int a7) {
    float v7 = (float)(a6 >> 24 & 0xFF) / 255.0f;
    float v13 = (float)(a6 >> 16 & 0xFF) / 255.0f;
    float v14 = (float)(a6 >> 8 & 0xFF) / 255.0f;
    float v15 = (float)(a6 & 0xFF) / 255.0f;
    float v16 = (float)(a7 >> 24 & 0xFF) / 255.0f;
    float v17 = (float)(a7 >> 16 & 0xFF) / 255.0f;
    float v18 = (float)(a7 >> 8 & 0xFF) / 255.0f;
    float v19 = (float)(a7 & 0xFF) / 255.0f;
    GlStateManager::disableTexture();
    GlStateManager::enableBlend();
    GlStateManager::disableAlphaTest();
    GlStateManager::blendFunc(5u, 6u);
    GlStateManager::shadeModel(0LL);
    Tesselator* tesselator = Tesselator::getInstance();
    BufferBuilder* builder = tesselator->getBuilder();
    builder->begin();
    builder->color(v13, v14, v15, v7);
    builder->vertex(a4, a3, field_0);
    builder->vertex(a2, a3, field_0);
    builder->color(v17, v18, v19, v16);
    builder->vertex(a2, a5, field_0);
    builder->vertex(a4, a5, field_0);
    builder->end();
    GlStateManager::shadeModel(0LL);
    GlStateManager::disableBlend();
    GlStateManager::enableAlphaTest();
    GlStateManager::enableTexture();
}

void GuiComponent::blit(int x, int y, int sx, int sy, int w, int h) {
    Tesselator* tesselator = Tesselator::getInstance();
    BufferBuilder* builder = tesselator->getBuilder();
    builder->begin();

    const float frac = 1.0f / 256.0f;

    Minecraft* minecraft = Minecraft::GetInstance();

    float so = minecraft->mWidth * 0.75f / minecraft->mDisplayWidth / Gui::sGuiScale;
    float vo = 0.75f / Gui::sGuiScale;
    float to = 0.75f / Gui::sGuiScale;

    float fx = floorf(x * Gui::sGuiScale) / Gui::sGuiScale;
    float fy = floorf(y * Gui::sGuiScale) / Gui::sGuiScale;
    float fw = floorf(w * Gui::sGuiScale) / Gui::sGuiScale;
    float fh = floorf(h * Gui::sGuiScale) / Gui::sGuiScale;

    builder->vertexUV(fx + 0.0f - so, fy + fh - vo, field_0, sx * frac, (h + sy) * frac);
    builder->vertexUV(fx + fw - so, fy + fh - vo, field_0, (w + sx) * frac, (h + sy) * frac);
    builder->vertexUV(fx + fw - so, fy + 0.0f - to, field_0, (w + sx) * frac, sy * frac);
    builder->vertexUV(fx + 0.0f - so, fy + 0.0f - to, field_0, sx * frac, sy * frac);
    return builder->end();
}
