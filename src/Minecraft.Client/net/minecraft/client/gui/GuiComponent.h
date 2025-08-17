#pragma once

#include <string>

class Font;

class GuiComponent {
public:
    GuiComponent();
    void fill(int x1, int y1, int x2, int y2, int color);
    void drawString(Font* font, const std::wstring& str, int a4, int a5, int a6);
    void drawCenteredString(Font* font, const std::wstring& str, int a4, int a5, int a6);
    void fillGradient(int, int, int, int, int, int);
    void blit(int, int, int, int, int, int);

    float field_0 = 0.0f;
};
