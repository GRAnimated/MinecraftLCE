#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ServerboundKeepAlivePacket : public Packet,
                                   public std::enable_shared_from_this<ServerboundKeepAlivePacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundKeepAlivePacket();

    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    EPacketType getPacketId() override;
    void handle(PacketListener* listener) override;

    int m_id;
};
