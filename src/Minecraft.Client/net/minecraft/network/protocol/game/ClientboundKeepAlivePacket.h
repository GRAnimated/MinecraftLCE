#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundKeepAlivePacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundKeepAlivePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundKeepAlivePacket();

    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    EPacketType getPacketId() override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;
    bool isAync() override;

    int mId;
};
