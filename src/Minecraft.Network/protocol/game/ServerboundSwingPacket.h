#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundSwingPacket : public Packet, public std::enable_shared_from_this<ServerboundSwingPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundSwingPacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    EPacketType getPacketId() override;

private:
    int field_28;
};
