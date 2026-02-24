#pragma once

#include "net/minecraft/network/protocol/Packet.h"

// PACKET STUB
class MapSelectInfoPacket : public Packet, public std::enable_shared_from_this<MapSelectInfoPacket> {
public:
    static std::shared_ptr<Packet> create();

    MapSelectInfoPacket(arrayWithLength<uchar>, bool);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    char m_fill[0x18];
};
