#pragma once

#include "Minecraft.Network/protocol/Packet.h"
#include "Minecraft.World/entity/Entity.h"

class ClientboundAddGlobalEntityPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundAddGlobalEntityPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAddGlobalEntityPacket();
    ClientboundAddGlobalEntityPacket(std::shared_ptr<Entity> entity);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getId();
    int getX();
    int getY();
    int getZ();
    int getType();

private:
    int id;
    int x;
    int y;
    int z;
    int type;
};
