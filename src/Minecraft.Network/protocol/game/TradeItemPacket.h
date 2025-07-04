#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class TradeItemPacket : public Packet,
                                       public std::enable_shared_from_this<TradeItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    TradeItemPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int dword18;
    int dword1C;
};
