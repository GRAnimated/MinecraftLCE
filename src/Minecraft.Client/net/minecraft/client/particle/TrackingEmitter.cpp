#include "net/minecraft/client/particle/TrackingEmitter.h"

#include "net/minecraft/client/particle/Particle.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/LevelListener.h"

TrackingEmitter::TrackingEmitter(Level* level, std::shared_ptr<Entity> entity, const ParticleType* type,
                                 int maxAge)
    : Particle(level, entity->mX, entity->getBoundingBox()->minY + (entity->mHeight / 2), entity->mZ,
               entity->mDeltaMovementX, entity->mDeltaMovementY, entity->mDeltaMovementZ) {
    mTarget = entity;
    mMaxAge = maxAge;
    mType = type;
    tick();
}

ePARTICLE_TYPE TrackingEmitter::getType() {
    return ePARTICLE_TYPE::ePARTICLE_TYPE_TrackingEmitter;
}

int TrackingEmitter::getParticleTexture() {
    return 3;
}

void TrackingEmitter::render(BufferBuilder*, std::shared_ptr<Entity>&, float, float, float, float, float,
                             float) {
    return;
}

// NON_MATCHING | score 1225
void TrackingEmitter::tick() {
    for (int i = 0; i < 16; i++) {
        double f1 = (mRandom.nextFloat() * 2) - 1.0;
        double f2 = (mRandom.nextFloat() * 2) - 1.0;
        double f3 = (mRandom.nextFloat() * 2) - 1.0;
        double expr = (f1 * f1 + f2 * f2 + f3 * f3);
        if (expr <= 1.0f) {
            mLevel->addParticle(
                mType, mTarget->mX + f1 * mTarget->mWidth / 4,
                mTarget->getBoundingBox()->minY + (mTarget->mHeight * 0.5) + f2 * mTarget->mHeight / 4,
                mTarget->mZ + f3 * mTarget->mWidth / 4, f1, f2 + 0.2, f3, arrayWithLength<int>());
        }
    }

    mAge++;
    if (mAge >= mMaxAge)
        remove();
}
