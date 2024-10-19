#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class Abilities;

class ClientboundPlayerAbilitiesPacket : public Packet, public std::enable_shared_from_this<ClientboundPlayerAbilitiesPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerAbilitiesPacket();
    ClientboundPlayerAbilitiesPacket(Abilities*, int);

    virtual EPacketType getPacketId() override;
    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;
    virtual bool canBeInvalidated() override;
    virtual bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

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
