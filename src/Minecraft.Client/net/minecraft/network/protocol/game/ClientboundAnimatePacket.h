#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundAnimatePacket : public Packet,
                                 public std::enable_shared_from_this<ClientboundAnimatePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAnimatePacket();
    ClientboundAnimatePacket(std::shared_ptr<Entity> entity, int unk);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getId();
    int getAction();

private:
    int mId;
    int mAction;
};
