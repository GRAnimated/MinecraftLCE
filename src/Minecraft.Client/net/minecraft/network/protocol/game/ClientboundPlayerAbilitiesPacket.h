#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class Abilities;

class ClientboundPlayerAbilitiesPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundPlayerAbilitiesPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerAbilitiesPacket();
    ClientboundPlayerAbilitiesPacket(Abilities*, int);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    void setInvulnerable(bool);
    void setFlying(bool);
    void setCanFly(bool);
    void setInstabuild(bool);
    void setFlyingSpeed(float);
    void setWalkingSpeed(float);
    void setCanBuild(bool);
    bool isInvulnerable();
    bool isFlying();
    bool canFly();
    bool canInstabuild();
    bool canBuild();
    float getFlyingSpeed();
    float getWalkingSpeed();
    int getPlayerId();

    bool mIsInvulnerable;
    bool mIsFlying;
    bool mIsEnableFly;
    bool mIsInstabuild;
    float mFlyingSpeed;
    float mWalkingSpeed;
    bool mIsEnableBuild;
    int mPlayerId;
};
