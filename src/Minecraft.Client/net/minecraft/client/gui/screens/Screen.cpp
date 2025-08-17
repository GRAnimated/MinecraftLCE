#include "net/minecraft/client/gui/screens/Screen.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/gui/components/Button.h"
#include "net/minecraft/client/gui/components/GuiParticles.h"
#include "net/minecraft/client/sounds/SoundEngine.h"
#include "net/minecraft/sounds/SoundEvents.h"

Screen::Screen() {
    mMinecraft = nullptr;
    mWidth = 0;
    mHeight = 0;
    byte_38 = false;
    mFont = nullptr;
    mGuiParticles = nullptr;
    mCurrentButton = nullptr;
}

void Screen::render(int x, int y, float) {
    for (auto& button : mButtons) {
        button->render(mMinecraft, x, y);
    }
}

void Screen::mouseClicked(int x, int y, int key) {
    if (key == 0) {
        auto end = mButtons.end();  // why is this before the loop??
        for (auto it = mButtons.begin(); it != end; ++it) {
            Button* button = *it;
            if (button->clicked(mMinecraft, x, y)) {
                mCurrentButton = button;
                mMinecraft->mSoundEngine->playUI(SoundEvents::RANDOM_CLICK, 1.0f, 1.0f);
                buttonClicked(button);
            }
        }
    }
}

void Screen::keyPressed(wchar_t key, int id) {
    if (id == 28) {
        mMinecraft->setScreen(0);
    }
}

void Screen::mouseReleased(int x, int y, int key) {
    if (mCurrentButton && key == 0) {
        mCurrentButton->released(x, y);
        mCurrentButton = nullptr;
    }
}

void Screen::buttonClicked(Button* button) {}

void Screen::init(Minecraft* minecraft, int width, int height) {
    mGuiParticles = new GuiParticles(minecraft);

    mMinecraft = minecraft;
    mFont = minecraft->mFont;
    mWidth = width;
    mHeight = height;
    mButtons.clear();
    init();
}

void Screen::setSize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

void Screen::init() {}

void Screen::updateEvents() {}

void Screen::mouseEvent() {}

void Screen::keyboardEvent() {}

void Screen::tick() {}

void Screen::removed() {}

void Screen::renderBackground() {
    renderBackground(0);
}

void Screen::renderBackground(int unk) {
    if (mMinecraft->mLevel) {
        return fillGradient(0, 0, mWidth, mHeight, 0xC0101010, 0xD0101010);
    } else
        return renderDirtBackground(unk);
}

void Screen::renderDirtBackground(int unk) {}

bool Screen::isPauseScreen() {
    return true;
}

void Screen::confirmResult(bool, int) {}

void Screen::tabPressed() {}
