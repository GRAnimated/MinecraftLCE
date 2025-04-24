#pragma once

#include "Minecraft.Client/gui/GuiComponent.h"
class Button;
class Minecraft;

class Screen : GuiComponent {
    virtual void render(int, int, float);
    virtual void keyPressed(wchar_t key, int);
    virtual void mouseClicked(int, int, int);
    virtual void mouseReleased(int, int, int);
    virtual void buttonClicked(Button* button);
    virtual void init(Minecraft*, int, int);
    virtual void init();
    virtual void setSize(int width, int height);
    virtual void updateEvents();
    virtual void mouseEvent();
    virtual void keyboardEvent();
    virtual void tick();
    virtual void removed();
    virtual void renderBackground();
    virtual void renderBackground(int);
    virtual void renderDirtBackground(int);
    virtual bool isPauseScreen();
    virtual void confirmResult(bool, int);
    virtual void tabPressed();

    unsigned char padding[0x50];
};