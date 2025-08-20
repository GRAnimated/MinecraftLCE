#pragma once

#include "net/minecraft/network/protocol/Packet.h"

// PACKET STUB
class ClientboundBlockUpdatePacket : public Packet,
                                     public std::enable_shared_from_this<ClientboundBlockUpdatePacket> {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};
