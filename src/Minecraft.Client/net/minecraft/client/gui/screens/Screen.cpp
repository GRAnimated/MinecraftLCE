#include "net/minecraft/client/gui/screens/Screen.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/gui/components/Button.h"
#include "net/minecraft/client/gui/components/GuiParticles.h"
#include "net/minecraft/client/sounds/SoundEngine.h"
#include "net/minecraft/sounds/SoundEvents.h"

Screen::Screen() {
    m_minecraft = nullptr;
    m_width = 0;
    m_height = 0;
    m_byte38 = false;
    m_font = nullptr;
    m_guiParticles = nullptr;
    m_currentButton = nullptr;
}

void Screen::render(int x, int y, float) {
    for (auto& button : m_buttons) {
        button->render(m_minecraft, x, y);
    }
}

void Screen::mouseClicked(int x, int y, int key) {
    if (key == 0) {
        auto end = m_buttons.end();  // why is this before the loop??
        for (auto it = m_buttons.begin(); it != end; ++it) {
            Button* button = *it;
            if (button->clicked(m_minecraft, x, y)) {
                m_currentButton = button;
                m_minecraft->m_soundEngine->playUI(SoundEvents::RANDOM_CLICK, 1.0f, 1.0f);
                buttonClicked(button);
            }
        }
    }
}

void Screen::keyPressed(wchar_t key, int id) {
    if (id == 28) {
        m_minecraft->setScreen(0);
    }
}

void Screen::mouseReleased(int x, int y, int key) {
    if (m_currentButton && key == 0) {
        m_currentButton->released(x, y);
        m_currentButton = nullptr;
    }
}

void Screen::buttonClicked(Button* button) {}

void Screen::init(Minecraft* minecraft, int width, int height) {
    m_guiParticles = new GuiParticles(minecraft);

    m_minecraft = minecraft;
    m_font = minecraft->m_font;
    m_width = width;
    m_height = height;
    m_buttons.clear();
    init();
}

void Screen::setSize(int width, int height) {
    m_width = width;
    m_height = height;
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
    if (m_minecraft->m_level) {
        return fillGradient(0, 0, m_width, m_height, 0xC0101010, 0xD0101010);
    } else
        return renderDirtBackground(unk);
}

void Screen::renderDirtBackground(int unk) {}

bool Screen::isPauseScreen() {
    return true;
}

void Screen::confirmResult(bool, int) {}

void Screen::tabPressed() {}
