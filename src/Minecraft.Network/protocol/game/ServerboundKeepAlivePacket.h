#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundKeepAlivePacket : public Packet, public std::enable_shared_from_this<ServerboundKeepAlivePacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundKeepAlivePacket();

    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual EPacketType getPacketId() override;
    virtual void handle(PacketListener* listener) override;

    int mId;
};
