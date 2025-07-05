#pragma once

#include "Minecraft.Network/protocol/Packet.h"
#include "Minecraft.World/entity/Entity.h"

class ServerboundMoveVehiclePacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundMoveVehiclePacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundMoveVehiclePacket();
    ServerboundMoveVehiclePacket(std::shared_ptr<Entity> entity);
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
