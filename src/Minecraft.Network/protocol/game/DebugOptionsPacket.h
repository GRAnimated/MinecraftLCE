#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class DebugOptionsPacket : public Packet,
                                       public std::enable_shared_from_this<DebugOptionsPacket> {
public:
    static std::shared_ptr<Packet> create();

    DebugOptionsPacket();
    DebugOptionsPacket(unsigned int unk1);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int dword18;
};
