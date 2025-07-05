#include "ClientboundMoveVehiclePacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundMoveVehiclePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundMoveVehiclePacket());
}

ClientboundMoveVehiclePacket::ClientboundMoveVehiclePacket() {}

ClientboundMoveVehiclePacket::ClientboundMoveVehiclePacket(std::shared_ptr<Entity> entity) {
    x = entity->mX;
    y = entity->mY;
    z = entity->mZ;
    yRot = entity->mYRot;
    xRot = entity->mXRot;
}

EPacketType ClientboundMoveVehiclePacket::getPacketId() {
    return EPacketType::_ClientboundMoveVehiclePacket;
}

void ClientboundMoveVehiclePacket::read(DataInputStream* input) {
    x = input->readDouble();
    y = input->readDouble();
    z = input->readDouble();
    yRot = input->readFloat();
    xRot = input->readFloat();
}

void ClientboundMoveVehiclePacket::write(DataOutputStream* output) {
    output->writeDouble(x);
    output->writeDouble(y);
    output->writeDouble(z);
    output->writeFloat(yRot);
    output->writeFloat(xRot);
}

void ClientboundMoveVehiclePacket::handle(PacketListener* listener) {
    listener->handleMoveVehicle(shared_from_this());
}

double ClientboundMoveVehiclePacket::getX() {
    return x;
}

double ClientboundMoveVehiclePacket::getY() {
    return y;
}

double ClientboundMoveVehiclePacket::getZ() {
    return z;
}

float ClientboundMoveVehiclePacket::getYRot() {
    return yRot;
}

float ClientboundMoveVehiclePacket::getXRot() {
    return xRot;
}
