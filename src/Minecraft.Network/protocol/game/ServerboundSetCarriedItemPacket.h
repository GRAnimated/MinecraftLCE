#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundSetCarriedItemPacket : public Packet, public std::enable_shared_from_this<ServerboundSetCarriedItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundSetCarriedItemPacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    EPacketType getPacketId() override;

private:
    int field_28;
};
