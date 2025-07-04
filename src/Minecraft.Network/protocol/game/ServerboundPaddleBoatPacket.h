#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundPaddleBoatPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundPaddleBoatPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundPaddleBoatPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    bool getLeft();
    bool getRight();

private:
    bool left;
    bool right;
};
