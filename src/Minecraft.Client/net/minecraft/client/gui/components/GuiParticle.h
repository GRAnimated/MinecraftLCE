#pragma once

class GuiParticles;

class GuiParticle {
public:
    void tick();  // the Wii U Edition symbol includes a GuiParticles* parameter, but it mismatches in
                  // GuiParticles if it's included
    void remove();
    void preTick();

    double double_0;
    double double_8;
    double double_10;
    double double_18;
    double double_20;
    double double_28;
    double double_30;
    bool byte_38;
    int dword_3c;
    int dword_40;
    int dword_44;
    double double_48;
    double double_50;
    double double_58;
    double double_60;
    double double_68;
    double double_70;
    double double_78;
    double double_80;
};
