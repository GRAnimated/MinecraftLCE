#pragma once

#include "net/minecraft/client/gui/GuiComponent.h"
#include <string>

class Minecraft;
class Random;
class BossHealthOverlay;

class Gui : public GuiComponent {
public:
    static float sGuiScale;  // Used in Gui::render and GuiComponent::blit

    Gui(Minecraft* mc);

    std::wstring sub_71005806DC(int);  // I don't have a damn clue what text it actually returns
    std::wstring sub_710054BD68(int);

    void* m_qword8;
    void* m_qword10;
    Random* m_random;
    Minecraft* m_minecraft;
    void* m_qword28;
    void* m_qword30;
    void* m_qword38;
    int m_dword40;
    int m_dword44;
    std::wstring m_string48;
    std::wstring m_string60;
    std::wstring m_string78;
    std::wstring m_string90;
    int m_dwordA8;
    int m_dwordAc;
    int m_dwordB0;
    int m_dwordB4;
    bool m_byteB8;
    BossHealthOverlay* m_bossHealthOverlay[4];
    int m_dwordE0;
    float m_dwordE4;
    void* m_qwordE8;
    void* m_qwordF0;
    void* m_qwordF8;
    void* m_qword100;
    void* m_qword108;
    void* m_qword110;
    void* m_qword118;
    void* m_qword120;
    int m_dword128;
    float m_dword12C;
    char m_filler[184];
};
