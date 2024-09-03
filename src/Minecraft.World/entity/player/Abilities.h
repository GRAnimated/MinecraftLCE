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
    void getFlyingSpeed();
    void setFlyingSpeed(float flyingSpeed);
    void getWalkingSpeed();
    void setWalkingSpeed(float walkingSpeed);
    void write(DataOutputStream* dataOutputStream);
    void read(DataInputStream* dataInputStream);

    bool isInvulnerable = false;
    bool isFlying = false;
    bool isEnableFly = false;
    bool isInstabuild = false;
    bool isEnableBuild = true;
    float flySpeed = 0.05f;
    float walkSpeed = 0.1f;
};