#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class Item;

class ClientboundCooldownPacket : public Packet,
                                  public std::enable_shared_from_this<ClientboundCooldownPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundCooldownPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    Item* item;
    int cooldown;
};
