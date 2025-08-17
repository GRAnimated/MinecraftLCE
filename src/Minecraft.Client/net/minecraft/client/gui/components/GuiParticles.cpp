#include "net/minecraft/client/gui/components/GuiParticles.h"

#include "net/minecraft/client/gui/components/GuiParticle.h"

GuiParticles::GuiParticles(Minecraft* minecraft) : mMinecraft(minecraft) {}

void GuiParticles::tick() {
    for (unsigned int i = 0; i < mParticles.size(); ++i) {
        GuiParticle* particle = mParticles[i];
        particle->preTick();
        particle->tick();

        if (particle->byte_38) {
            mParticles.erase(mParticles.begin() + i);
            --i;  // adjust index after removal
        }
    }
}
