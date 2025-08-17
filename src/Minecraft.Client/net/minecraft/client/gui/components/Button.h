#pragma once

#include "net/minecraft/client/gui/GuiComponent.h"

class Minecraft;

class Button : public GuiComponent {
public:
    Button(int, int, int, const std::wstring&);
    Button(int, int, int, int, int, const std::wstring&);
    void init(int, int, int, int, int, const std::wstring&);
    virtual int getYImage(bool);
    virtual void render(Minecraft*, int, int);
    virtual void renderBg(Minecraft*, int, int);
    virtual void released(int, int);
    virtual bool clicked(Minecraft*, int, int);

    int mWidth;
    int mHeight;
    int mX;
    int mY;
    std::wstring mButtonText;
    int mId;
    bool mIsActive;
    bool mIsVisible;
};
