#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class DisconnectPacket : public Packet, public std::enable_shared_from_this<DisconnectPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum eDisconnectReason {
        _0 = 0,
        Closed = 2,
        Kicked = 8,
        Timeout = 10,
        Overflow = 11,
        _29 = 29,
    };

    DisconnectPacket();

    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    EPacketType getPacketId() override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    eDisconnectReason mReason;
};
