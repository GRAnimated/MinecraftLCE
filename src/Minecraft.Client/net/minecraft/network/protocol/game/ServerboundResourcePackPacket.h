#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ServerboundResourcePackPacket : public Packet,
                                      public std::enable_shared_from_this<ServerboundResourcePackPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundResourcePackPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int resourcePackId;
};
