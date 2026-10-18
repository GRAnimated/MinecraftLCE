#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class AABB;

class SpikeFeature : public Feature {
public:
    class EndSpike {
    public:
        EndSpike(int centerX, int centerZ, int radius, int height, bool guarded);
        ~EndSpike();
        int getCenterX();
        int getCenterZ();
        int getRadius();
        int getHeight();
        bool isGuarded();
        AABB* getTopBoundingBox();

        int m_centerX;
        int m_centerZ;
        int m_radius;
        int m_height;
        bool m_guarded;
        AABB* m_bounds;
    };

    SpikeFeature();
    ~SpikeFeature() override;
    bool place(Level*, Random&, const BlockPos&) override;
    void setSpike(EndSpike*);
    void setCrystalInvulnerable(bool);
    void setCrystalBeamTarget(const BlockPos&);

private:
    bool m_crystalInvulnerable;
    EndSpike* m_spike;
    BlockPos* m_beamTarget;
};

static_assert(sizeof(SpikeFeature::EndSpike) == 0x20, "EndSpike ABI");
static_assert(sizeof(SpikeFeature) == 0x20, "SpikeFeature ABI");
