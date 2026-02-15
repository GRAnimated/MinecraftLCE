#include "ClientboundAddExperienceOrbPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundAddExperienceOrbPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAddExperienceOrbPacket());
}

ClientboundAddExperienceOrbPacket::ClientboundAddExperienceOrbPacket() {
    m_x = 0;
    m_z = 0;
    m_value = 0;
    m_y = 0;
    m_id = 0;
}

int ClientboundAddExperienceOrbPacket::getEstimatedSize() {
    return 18;
}

EPacketType ClientboundAddExperienceOrbPacket::getPacketId() {
    return EPacketType::_ClientboundAddExperienceOrbPacket;
}

void ClientboundAddExperienceOrbPacket::read(DataInputStream* input) {
    m_id = input->readInt();
    m_x = input->readInt();
    m_y = input->readInt();
    m_z = input->readInt();
    m_value = input->readShort();
}

void ClientboundAddExperienceOrbPacket::write(DataOutputStream* output) {
    output->writeInt(m_id);
    output->writeInt(m_x);
    output->writeInt(m_y);
    output->writeInt(m_z);
    output->writeShort(m_value);
}

void ClientboundAddExperienceOrbPacket::handle(PacketListener* listener) {
    listener->handleAddExperienceOrb(shared_from_this());
}

int ClientboundAddExperienceOrbPacket::getId() {
    return m_id;
}

int ClientboundAddExperienceOrbPacket::getX() {
    return m_x;
}

int ClientboundAddExperienceOrbPacket::getY() {
    return m_y;
}

int ClientboundAddExperienceOrbPacket::getZ() {
    return m_z;
}

int ClientboundAddExperienceOrbPacket::getValue() {
    return m_value;
}
