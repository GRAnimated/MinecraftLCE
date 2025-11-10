#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundSetHealthPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundSetHealthPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetHealthPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    float getHealth();
    int getFood();
    float getSaturation();

private:
    int dword18; // 0x28
    int dword1C; // 0x2c
    int dword20; // 0x30
    float health; // 0x34
    int food; // 0x38
    float saturation; // 0x3c
};
