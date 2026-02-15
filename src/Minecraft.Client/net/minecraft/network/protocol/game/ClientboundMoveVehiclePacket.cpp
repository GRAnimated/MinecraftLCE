#include "ClientboundMoveVehiclePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundMoveVehiclePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundMoveVehiclePacket());
}

ClientboundMoveVehiclePacket::ClientboundMoveVehiclePacket() {}

ClientboundMoveVehiclePacket::ClientboundMoveVehiclePacket(std::shared_ptr<Entity> entity) {
    m_x = entity->m_x;
    m_y = entity->m_y;
    m_z = entity->m_z;
    m_yRot = entity->m_yRot;
    m_xRot = entity->m_xRot;
}

EPacketType ClientboundMoveVehiclePacket::getPacketId() {
    return EPacketType::_ClientboundMoveVehiclePacket;
}

void ClientboundMoveVehiclePacket::read(DataInputStream* input) {
    m_x = input->readDouble();
    m_y = input->readDouble();
    m_z = input->readDouble();
    m_yRot = input->readFloat();
    m_xRot = input->readFloat();
}

void ClientboundMoveVehiclePacket::write(DataOutputStream* output) {
    output->writeDouble(m_x);
    output->writeDouble(m_y);
    output->writeDouble(m_z);
    output->writeFloat(m_yRot);
    output->writeFloat(m_xRot);
}

void ClientboundMoveVehiclePacket::handle(PacketListener* listener) {
    listener->handleMoveVehicle(shared_from_this());
}

double ClientboundMoveVehiclePacket::getX() {
    return m_x;
}

double ClientboundMoveVehiclePacket::getY() {
    return m_y;
}

double ClientboundMoveVehiclePacket::getZ() {
    return m_z;
}

float ClientboundMoveVehiclePacket::getYRot() {
    return m_yRot;
}

float ClientboundMoveVehiclePacket::getXRot() {
    return m_xRot;
}
