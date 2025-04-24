#pragma once

#include "Minecraft.Network/protocol/Packet.h"
#include <memory>

class ClientboundAwardStatPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundAwardStatPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAwardStatPacket();
    ~ClientboundAwardStatPacket() override;
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool isAync() override;

private:
    int stat;
    arrayWithLength<unsigned char> data;
};
