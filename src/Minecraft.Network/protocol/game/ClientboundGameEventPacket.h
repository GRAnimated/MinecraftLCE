#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundGameEventPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundGameEventPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundGameEventPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getEvent();
    float getParam();
    int getPlayerIndex();

private:
    int mEvent;
    float mParam;
    int mPlayerIndex;
};
