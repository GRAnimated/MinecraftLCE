#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class Abilities;

class ServerboundPlayerAbilitiesPacket
    : public Packet,
      public std::enable_shared_from_this<ServerboundPlayerAbilitiesPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundPlayerAbilitiesPacket();
    explicit ServerboundPlayerAbilitiesPacket(Abilities*);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    void setInvulnerable(bool);
    void setFlying(bool);
    void setCanFly(bool);
    void setInstabuild(bool);
    void setFlyingSpeed(float);
    void setWalkingSpeed(float);
    bool isInvulnerable();
    bool isFlying();
    bool canFly();
    bool canInstabuild();

    bool m_isInvulnerable;
    bool m_isFlying;
    bool m_isEnableFly;
    bool m_isInstabuild;
    float m_flyingSpeed;
    float m_walkingSpeed;
};

static_assert(sizeof(ServerboundPlayerAbilitiesPacket) == 0x38, "Serverbound abilities Switch layout");
