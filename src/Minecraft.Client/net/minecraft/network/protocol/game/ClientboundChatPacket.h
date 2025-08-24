#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundChatPacket : public Packet, public std::enable_shared_from_this<ClientboundChatPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum EChatPacketMessage {};

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};
