#include "ServerboundMoveVehiclePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundMoveVehiclePacket::create() {
    return std::shared_ptr<Packet>(new ServerboundMoveVehiclePacket());
}

ServerboundMoveVehiclePacket::ServerboundMoveVehiclePacket() {}

ServerboundMoveVehiclePacket::ServerboundMoveVehiclePacket(std::shared_ptr<Entity> entity) {
    m_x = entity->m_x;
    m_y = entity->m_y;
    m_z = entity->m_z;
    m_yRot = entity->m_yRot;
    m_xRot = entity->m_xRot;
}

EPacketType ServerboundMoveVehiclePacket::getPacketId() {
    return EPacketType::_ServerboundMoveVehiclePacket;
}

void ServerboundMoveVehiclePacket::read(DataInputStream* input) {
    m_x = input->readDouble();
    m_y = input->readDouble();
    m_z = input->readDouble();
    m_yRot = input->readFloat();
    m_xRot = input->readFloat();
}

void ServerboundMoveVehiclePacket::write(DataOutputStream* output) {
    output->writeDouble(m_x);
    output->writeDouble(m_y);
    output->writeDouble(m_z);
    output->writeFloat(m_yRot);
    output->writeFloat(m_xRot);
}

void ServerboundMoveVehiclePacket::handle(PacketListener* listener) {
    listener->handleMoveVehicle(shared_from_this());
}

double ServerboundMoveVehiclePacket::getX() {
    return m_x;
}

double ServerboundMoveVehiclePacket::getY() {
    return m_y;
}

double ServerboundMoveVehiclePacket::getZ() {
    return m_z;
}

float ServerboundMoveVehiclePacket::getYRot() {
    return m_yRot;
}

float ServerboundMoveVehiclePacket::getXRot() {
    return m_xRot;
}
