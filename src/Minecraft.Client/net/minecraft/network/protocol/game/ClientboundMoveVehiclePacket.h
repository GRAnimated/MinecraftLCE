#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/entity/Entity.h"

class ClientboundMoveVehiclePacket : public Packet,
                                     public std::enable_shared_from_this<ClientboundMoveVehiclePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundMoveVehiclePacket();
    ClientboundMoveVehiclePacket(std::shared_ptr<Entity> entity);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    double getX();
    double getY();
    double getZ();
    float getYRot();
    float getXRot();

private:
    double x;
    double y;
    double z;
    float yRot;
    float xRot;
};
