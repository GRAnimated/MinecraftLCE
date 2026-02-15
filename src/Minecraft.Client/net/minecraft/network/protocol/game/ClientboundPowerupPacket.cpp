#include "ClientboundPowerupPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundPowerupPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPowerupPacket());
}

ClientboundPowerupPacket::ClientboundPowerupPacket() {
    m_powerupId = -1;
    m_powerupTime = -1;
}

int ClientboundPowerupPacket::getEstimatedSize() {
    return 2;
}

EPacketType ClientboundPowerupPacket::getPacketId() {
    return EPacketType::_ClientboundPowerupPacket;
}

void ClientboundPowerupPacket::read(DataInputStream* input) {
    m_powerupId = input->readInt();
    m_powerupTime = input->readInt();
}

void ClientboundPowerupPacket::write(DataOutputStream* output) {
    output->writeInt(m_powerupId);
    output->writeInt(m_powerupTime);
}

void ClientboundPowerupPacket::handle(PacketListener* listener) {
    listener->handlePowerup(shared_from_this());
}

int ClientboundPowerupPacket::getPowerupID() {
    return m_powerupId;
}

int ClientboundPowerupPacket::getPowerupTime() {
    return m_powerupTime;
}
