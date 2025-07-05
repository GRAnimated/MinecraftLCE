#include "ServerboundMoveVehiclePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundMoveVehiclePacket::create() {
    return std::shared_ptr<Packet>(new ServerboundMoveVehiclePacket());
}

ServerboundMoveVehiclePacket::ServerboundMoveVehiclePacket() {}

ServerboundMoveVehiclePacket::ServerboundMoveVehiclePacket(std::shared_ptr<Entity> entity) {
    x = entity->mX;
    y = entity->mY;
    z = entity->mZ;
    yRot = entity->mYRot;
    xRot = entity->mXRot;
}

EPacketType ServerboundMoveVehiclePacket::getPacketId() {
    return EPacketType::_ServerboundMoveVehiclePacket;
}

void ServerboundMoveVehiclePacket::read(DataInputStream* input) {
    x = input->readDouble();
    y = input->readDouble();
    z = input->readDouble();
    yRot = input->readFloat();
    xRot = input->readFloat();
}

void ServerboundMoveVehiclePacket::write(DataOutputStream* output) {
    output->writeDouble(x);
    output->writeDouble(y);
    output->writeDouble(z);
    output->writeFloat(yRot);
    output->writeFloat(xRot);
}

void ServerboundMoveVehiclePacket::handle(PacketListener* listener) {
    listener->handleMoveVehicle(shared_from_this());
}

double ServerboundMoveVehiclePacket::getX() {
    return x;
}

double ServerboundMoveVehiclePacket::getY() {
    return y;
}

double ServerboundMoveVehiclePacket::getZ() {
    return z;
}

float ServerboundMoveVehiclePacket::getYRot() {
    return yRot;
}

float ServerboundMoveVehiclePacket::getXRot() {
    return xRot;
}
