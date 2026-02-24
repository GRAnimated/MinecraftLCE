#pragma once

#include "net/minecraft/client/gui/GuiComponent.h"
#include <vector>

class Button;
class GuiParticles;
class Minecraft;

class Screen : public GuiComponent {
public:
    Screen();

    virtual ~Screen();
    virtual void render(int, int, float);
    virtual void keyPressed(wchar_t key, int);
    virtual void mouseClicked(int, int, int);
    virtual void mouseReleased(int, int, int);
    virtual void buttonClicked(Button* button);
    virtual void init(Minecraft*, int, int);
    virtual void setSize(int width, int height);  // Swapped with init() on Switch Edition for some reason
    virtual void init();
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

    Minecraft* m_minecraft;
    int m_width;
    int m_height;
    std::vector<Button*> m_buttons;
    bool m_byte38;
    Font* m_font;
    GuiParticles* m_guiParticles;
    Button* m_currentButton;
};
