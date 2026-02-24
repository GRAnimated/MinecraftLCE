#include "net/minecraft/client/gui/components/GuiParticles.h"

#include "net/minecraft/client/gui/components/GuiParticle.h"

GuiParticles::GuiParticles(Minecraft* minecraft) : m_minecraft(minecraft) {}

void GuiParticles::tick() {
    for (unsigned int i = 0; i < m_particles.size(); ++i) {
        GuiParticle* particle = m_particles[i];
        particle->preTick();
        particle->tick();

        if (particle->m_byte38) {
            m_particles.erase(m_particles.begin() + i);
            --i;  // adjust index after removal
        }
    }
}
