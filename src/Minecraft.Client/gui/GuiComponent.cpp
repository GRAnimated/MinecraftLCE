#include "Minecraft.Client/gui/GuiComponent.h"

#include "Minecraft.Client/gui/Font.h"
#include "Minecraft.Client/renderer/BufferBuilder.h"
#include "Minecraft.Client/renderer/GlStateManager.h"
#include "Minecraft.Client/renderer/Tesselator.h"

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
