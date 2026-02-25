#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundSetHealthPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundSetHealthPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetHealthPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    float getHealth();
    int getFood();
    float getSaturation();

private:
    int m_dword28;
    int m_dword2C;
    int m_dword30;
    float m_health;
    int m_food;
    float m_saturation;
};
