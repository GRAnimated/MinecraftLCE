#include "ClientboundSetHealthPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetHealthPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetHealthPacket());
}

ClientboundSetHealthPacket::ClientboundSetHealthPacket() {
    m_health = 0.0;
    m_food = 0.0;
    m_saturation = 0.0;
    m_dword28 = 0;
    m_dword2C = -1;
}

int ClientboundSetHealthPacket::getEstimatedSize() {
    return 16;
}

EPacketType ClientboundSetHealthPacket::getPacketId() {
    return EPacketType::_ClientboundSetHealthPacket;
}

void ClientboundSetHealthPacket::read(DataInputStream* input) {
    m_health = input->readFloat();
    m_food = input->readVarInt();
    m_saturation = input->readFloat();
    m_dword28 = input->readByte() & 0xFF;
    m_dword2C = input->readVarInt();
    m_dword30 = input->readVarInt();
}

void ClientboundSetHealthPacket::write(DataOutputStream* output) {
    output->writeFloat(m_health);
    output->writeVarInt(m_food);
    output->writeFloat(m_saturation);
    output->writeByte(m_dword28);
    output->writeVarInt(m_dword2C);
    output->writeVarInt(m_dword30);
}

void ClientboundSetHealthPacket::handle(PacketListener* listener) {
    listener->handleSetHealth(shared_from_this());
}

bool ClientboundSetHealthPacket::canBeInvalidated() {
    return true;
}

bool ClientboundSetHealthPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

float ClientboundSetHealthPacket::getHealth() {
    return m_health;
}

int ClientboundSetHealthPacket::getFood() {
    return m_food;
}

float ClientboundSetHealthPacket::getSaturation() {
    return m_saturation;
}
