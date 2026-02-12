#include "ClientboundDamageIndicatorPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundDamageIndicatorPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundDamageIndicatorPacket());
}

ClientboundDamageIndicatorPacket::ClientboundDamageIndicatorPacket() {
    m_x = 0.0;
    m_z = 0.0;
    m_allDirections = true;
}

int ClientboundDamageIndicatorPacket::getEstimatedSize() {
    return 9;
}

EPacketType ClientboundDamageIndicatorPacket::getPacketId() {
    return EPacketType::_ClientboundDamageIndicatorPacket;
}

void ClientboundDamageIndicatorPacket::read(DataInputStream* input) {
    m_x = input->readFloat();
    m_z = input->readFloat();
    m_allDirections = input->readBoolean();
}

void ClientboundDamageIndicatorPacket::write(DataOutputStream* output) {
    output->writeFloat(m_x);
    output->writeFloat(m_z);
    output->writeBoolean(m_allDirections);
}

void ClientboundDamageIndicatorPacket::handle(PacketListener* listener) {
    listener->handleDamageIndicator(shared_from_this());
}

float ClientboundDamageIndicatorPacket::getX() {
    return m_x;
}

float ClientboundDamageIndicatorPacket::getZ() {
    return m_z;
}

bool ClientboundDamageIndicatorPacket::isAllDirections() {
    return m_allDirections;
}
