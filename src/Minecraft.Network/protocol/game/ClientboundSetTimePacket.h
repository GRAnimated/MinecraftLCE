#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ClientboundSetTimePacket : public Packet, public std::enable_shared_from_this<ClientboundSetTimePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetTimePacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    int getEstimatedSize() override;
    bool isInvalidatedBy(std::shared_ptr<Packet>) override;
    bool isAync() override;
    EPacketType getPacketId() override;

private:
    long field_28;
    long field_30;
};
