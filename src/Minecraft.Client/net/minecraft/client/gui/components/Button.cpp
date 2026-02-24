#include "net/minecraft/client/gui/components/Button.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/texture/Textures.h"

Button::Button(int id, int x, int y, const std::wstring& name) {
    init(id, x, y, 200, 20, name);
}

Button::Button(int id, int x, int y, int width, int height, const std::wstring& name) {
    init(id, x, y, width, height, name);
}

void Button::init(int id, int x, int y, int width, int height, const std::wstring& name) {
    m_isActive = true;
    m_isVisible = true;
    m_id = id;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_buttonText = name;
}

int Button::getYImage(bool isHovered) {
    int res = 1;
    if (!m_isActive) {
        res = 0;
    } else if (isHovered) {
        res = 2;
    }
    return res;
}

void Button::render(Minecraft* minecraft, int x, int y) {
    if (!m_isVisible)
        return;

    Font* font = minecraft->m_font;
    int texture = minecraft->m_textures->loadTexture(8);
    GlStateManager::bindTexture(texture);
    GlStateManager::color4f(1.0f, 1.0f, 1.0f, 1.0f);

    bool hovered = (x >= m_x && y >= m_y && x < m_x + m_width && y < m_y + m_height);
    int yImage = getYImage(hovered);

    blit(m_x, m_y, 0, 46 + yImage * 20, m_width / 2, m_height);
    blit(m_x + m_width / 2, m_y, 200 - m_width / 2, 46 + yImage * 20, m_width / 2, m_height);

    renderBg(minecraft, x, y);

    if (!this->m_isActive) {
        drawCenteredString(font, m_buttonText, m_x + m_width / 2, m_y + (m_height - 8) / 2, -6250336);
    } else if (hovered) {
        drawCenteredString(font, m_buttonText, m_x + m_width / 2, m_y + (m_height - 8) / 2, 16777120);
    } else {
        drawCenteredString(font, m_buttonText, m_x + m_width / 2, m_y + (m_height - 8) / 2, 14737632);
    }
}

void Button::renderBg(Minecraft*, int, int) {}

void Button::released(int, int) {}

bool Button::clicked(Minecraft*, int x, int y) {
    if (!m_isActive)
        return false;
    if (m_x > x)
        return false;
    if (m_y > y)
        return false;
    if (m_width + m_x <= x)
        return false;
    return m_height + m_y > y;
}
