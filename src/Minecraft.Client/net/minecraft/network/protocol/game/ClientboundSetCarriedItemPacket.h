#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundSetCarriedItemPacket : public Packet,
                                        public std::enable_shared_from_this<ClientboundSetCarriedItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetCarriedItemPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int itemId;
};
