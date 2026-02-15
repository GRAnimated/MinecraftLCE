#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "types.h"
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
    char m_field28 = 0;
    int m_x = 0;
    int m_z = 0;
};

ASSERT_SIZEOF(XZPacket, 0x38)
