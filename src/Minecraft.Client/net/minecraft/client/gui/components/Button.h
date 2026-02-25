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

    int m_width;
    int m_height;
    int m_x;
    int m_y;
    std::wstring m_buttonText;
    int m_id;
    bool m_isActive;
    bool m_isVisible;
};
