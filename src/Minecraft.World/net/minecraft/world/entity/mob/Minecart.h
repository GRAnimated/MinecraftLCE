#pragma once

#include "net/minecraft/world/entity/Entity.h"

// Partial reconstruction. New virtuals follow the original Switch vtable order.
class Minecart : public Entity {
public:
    static void staticCtor();

    void setPos(double, double, double) override;
    void lerpMotion(double, double, double) override;

    virtual void destroy(DamageSource*);
    virtual double getMaxSpeed();
    virtual void activateMinecart(int, int, int, bool);
    virtual void moveOffTrack();
    virtual void moveAlongTrack(const BlockPos&, const BlockState*);
    virtual void applyNaturalSlowdown();
    virtual Vec3* getPosOffs(double, double, double, double);
    virtual Vec3* getPos(double, double, double);

    bool m_flipped;
    std::uint64_t m_field2B8;
    bool m_field2C0;
    int m_lerpSteps;
    double m_lerpX;
    double m_lerpY;
    double m_lerpZ;
    double m_lerpYRot;
    double m_lerpXRot;
    double m_lerpDeltaX;
    double m_lerpDeltaY;
    double m_lerpDeltaZ;
};

ASSERT_SIZEOF(Minecart, 0x308)
