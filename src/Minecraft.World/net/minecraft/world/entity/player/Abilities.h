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

    bool mIsInvulnerable = false;
    bool mIsFlying = false;
    bool mIsEnableFly = false;
    bool mIsInstabuild = false;
    bool mIsEnableBuild = true;
    float mFlySpeed = 0.05f;
    float mWalkSpeed = 0.1f;
};
