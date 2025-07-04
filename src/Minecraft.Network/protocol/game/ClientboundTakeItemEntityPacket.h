#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundTakeItemEntityPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundTakeItemEntityPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundTakeItemEntityPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getItemId();
    int getPlayerId();
    int getAmount();

private:
    int itemId;
    int playerId;
    int amount;
};
