#pragma once

class GuiParticles;

class GuiParticle {
public:
    void tick();  // the Wii U Edition symbol includes a GuiParticles* parameter, but it mismatches in
                  // GuiParticles if it's included
    void remove();
    void preTick();

    double m_double0;
    double m_double8;
    double m_double10;
    double m_double18;
    double m_double20;
    double m_double28;
    double m_double30;
    bool m_byte38;
    int m_dword3c;
    int m_dword40;
    int m_dword44;
    double m_double48;
    double m_double50;
    double m_double58;
    double m_double60;
    double m_double68;
    double m_double70;
    double m_double78;
    double m_double80;
};
