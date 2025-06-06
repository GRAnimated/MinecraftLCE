#include "Minecraft.Client/gui/components/Button.h"

#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/renderer/GlStateManager.h"
#include "Minecraft.Client/renderer/texture/Textures.h"

Button::Button(int id, int x, int y, const std::wstring& name) {
    init(id, x, y, 200, 20, name);
}

Button::Button(int id, int x, int y, int width, int height, const std::wstring& name) {
    init(id, x, y, width, height, name);
}

void Button::init(int id, int x, int y, int width, int height, const std::wstring& name) {
    mIsActive = true;
    mIsVisible = true;
    mId = id;
    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;
    mButtonText = name;
}

int Button::getYImage(bool isHovered) {
    int res = 1;
    if (!mIsActive) {
        res = 0;
    } else if (isHovered) {
        res = 2;
    }
    return res;
}

void Button::render(Minecraft* minecraft, int x, int y) {
    if (!mIsVisible)
        return;

    Font* font = minecraft->mDefaultFont;
    int texture = minecraft->mTextures->loadTexture(8);
    GlStateManager::bindTexture(texture);
    GlStateManager::color4f(1.0f, 1.0f, 1.0f, 1.0f);

    bool hovered = (x >= mX && y >= mY && x < mX + mWidth && y < mY + mHeight);
    int yImage = getYImage(hovered);

    blit(mX, mY, 0, 46 + yImage * 20, mWidth / 2, mHeight);
    blit(mX + mWidth / 2, mY, 200 - mWidth / 2, 46 + yImage * 20, mWidth / 2, mHeight);

    renderBg(minecraft, x, y);

    if (!this->mIsActive) {
        drawCenteredString(font, mButtonText, mX + mWidth / 2, mY + (mHeight - 8) / 2, -6250336);
    } else if (hovered) {
        drawCenteredString(font, mButtonText, mX + mWidth / 2, mY + (mHeight - 8) / 2, 16777120);
    } else {
        drawCenteredString(font, mButtonText, mX + mWidth / 2, mY + (mHeight - 8) / 2, 14737632);
    }
}

void Button::renderBg(Minecraft*, int, int) {}

void Button::released(int, int) {}

bool Button::clicked(Minecraft*, int x, int y) {
    if (!mIsActive)
        return false;
    if (mX > x)
        return false;
    if (mY > y)
        return false;
    if (mWidth + mX <= x)
        return false;
    return mHeight + mY > y;
}