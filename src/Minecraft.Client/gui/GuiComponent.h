#pragma once

#include <string>

class Font;

class GuiComponent {
public:
    GuiComponent();
    void fill(int, int, int, int, int);
    void drawString(Font*, std::wstring const&, int, int, int);
    void drawCenteredString(Font*, std::wstring const&, int, int, int);

    int field_0;
};
