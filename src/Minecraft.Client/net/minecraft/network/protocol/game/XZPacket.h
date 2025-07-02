#pragma once

#include "types.h"
#include "net/minecraft/network/protocol/Packet.h"
#include <memory>

class XZPacket : public Packet, public std::enable_shared_from_this<XZPacket> {
public:
    static std::shared_ptr<Packet> create();

    XZPacket();
    XZPacket(char field_28, int x, int z);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;

private:
    char field_28 = 0;
    int mX = 0;
    int mZ = 0;
};

ASSERT_SIZEOF(XZPacket, 0x38)