#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class KickPlayerPacket : public Packet, public std::enable_shared_from_this<KickPlayerPacket> {
public:
    static std::shared_ptr<Packet> create();

    KickPlayerPacket();
    KickPlayerPacket(unsigned char unk1);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    unsigned char m_byte18;
};
