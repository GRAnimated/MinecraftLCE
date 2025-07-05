#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class PlayerReadyPacket : public Packet,
                                       public std::enable_shared_from_this<PlayerReadyPacket> {
public:
    static std::shared_ptr<Packet> create();

    PlayerReadyPacket();
    PlayerReadyPacket(unsigned int playerId, bool ready);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    unsigned int mPlayerId;
    bool mReady;
};
