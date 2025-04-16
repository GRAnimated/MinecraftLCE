#pragma once

class Button;
class Minecraft;

class Screen {
public:
    virtual ~Screen();
    virtual void render(int, int, float);
    virtual void keyPressed(wchar_t, int);
    virtual void mouseClicked(int, int, int);
    virtual void mouseReleased(int, int, int);
    virtual void buttonClicked(Button*);
    virtual void init(Minecraft*, int, int);
    virtual void init();
    virtual void setSize(int, int);
    virtual void updateEvents();
    virtual void mouseEvent();
    virtual void keyboardEvent();
    virtual void tick();
    virtual void removed();
    virtual void renderBackground();
    virtual void renderBackground(int);
    virtual void renderDirtBackground(int);
    virtual void isPauseScreen();
    virtual void confirmResult(bool, int);
    virtual void tabPressed();
};
