#pragma once

class CompoundTag;
class DataOutputStream;
class DataInputStream;

class Abilities {
public:
    Abilities();
    bool operator==(const Abilities& abilities) const;

    void addSaveData(CompoundTag* compoundTag);
    void loadSaveData(CompoundTag* compoundTag);
    float getFlyingSpeed();
    void setFlyingSpeed(float flyingSpeed);
    float getWalkingSpeed();
    void setWalkingSpeed(float walkingSpeed);
    void write(DataOutputStream* dataOutputStream);
    void read(DataInputStream* dataInputStream);

    bool m_isInvulnerable = false;
    bool m_isFlying = false;
    bool m_isEnableFly = false;
    bool m_isInstabuild = false;
    bool m_isEnableBuild = true;
    float m_flySpeed = 0.05f;
    float m_walkSpeed = 0.1f;
};
