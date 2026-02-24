#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ServerboundSetCarriedItemPacket : public Packet,
                                        public std::enable_shared_from_this<ServerboundSetCarriedItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundSetCarriedItemPacket();
    ServerboundSetCarriedItemPacket(int);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getCarriedItem();

private:
    int m_carriedItem;
};
