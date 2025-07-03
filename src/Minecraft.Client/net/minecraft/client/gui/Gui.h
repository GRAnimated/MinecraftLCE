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

    void* qword8;
    void* qword10;
    Random* mRandom;
    Minecraft* mMinecraft;
    void* qword28;
    void* qword30;
    void* qword38;
    int dword40;
    int dword44;
    std::wstring string_48;
    std::wstring string_60;
    std::wstring string_78;
    std::wstring string_90;
    int dwordA8;
    int dwordAC;
    int dwordB0;
    int dwordB4;
    bool byteB8;
    BossHealthOverlay* mBossHealthOverlay[4];
    int dwordE0;
    float dwordE4;
    void* qwordE8;
    void* qwordF0;
    void* qwordF8;
    void* qword100;
    void* qword108;
    void* qword110;
    void* qword118;
    void* qword120;
    int dword128;
    float dword12C;
    char filler[184];
};
