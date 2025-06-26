#pragma once

#include "Minecraft.Client/gui/screens/Screen.h"

class TitleScreen : public Screen {
public:
    TitleScreen();

    void render(int, int, float) override;
    void keyPressed(wchar_t key, int) override;
    void buttonClicked(Button* button) override;
    void setSize(int width, int height) override;
    void tick() override;

    unsigned char size[0x28];
};
