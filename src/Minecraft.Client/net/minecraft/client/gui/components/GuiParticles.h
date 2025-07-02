#pragma once

#include "net/minecraft/client/gui/GuiComponent.h"
#include <vector>

class GuiParticle;
class Minecraft;

class GuiParticles : public GuiComponent {
public:
    GuiParticles(Minecraft* minecraft);
    void tick();

    std::vector<GuiParticle*> mParticles;
    Minecraft* mMinecraft;
};
