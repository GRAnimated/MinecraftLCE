#pragma once
#include "Minecraft.Client/gui/screens/Screen.h"

class TitleScreen : public Screen {
public:
    // unsure what the args are for any of these, assuming they're default.
    void render(int, int, float) override;
    void keyPressed(wchar_t key, int) override;
    void buttonClicked(Button* button) override;
    void setSize(int width, int height) override;
    void tick() override;

    TitleScreen();

    // assumed
    unsigned char padding[0x28];
};