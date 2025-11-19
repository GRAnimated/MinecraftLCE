#pragma once

#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/world/level/LevelListener.h"

class Particle;

class TrackingEmitter : public Particle {
public:
    TrackingEmitter(Level* level, std::shared_ptr<Entity> entity, const ParticleType* type, int param5);
    ~TrackingEmitter();

    void tick() override;
    ePARTICLE_TYPE getType() override;
    int getParticleTexture() override;
    void render(BufferBuilder*, std::shared_ptr<Entity>&, float, float, float, float, float, float) override;

    std::shared_ptr<Entity> mTarget;
    const ParticleType* mType;
};
