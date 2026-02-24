#include "ClientboundAddGlobalEntityPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/util/Mth.h"

std::shared_ptr<Packet> ClientboundAddGlobalEntityPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAddGlobalEntityPacket());
}

ClientboundAddGlobalEntityPacket::ClientboundAddGlobalEntityPacket() {
    m_id = -1;
    m_y = 0;
    m_z = 0;
    m_x = 0;
    m_type = 0;
}

ClientboundAddGlobalEntityPacket::ClientboundAddGlobalEntityPacket(std::shared_ptr<Entity> entity) {
    m_id = entity->getId();
    m_x = Mth::floor(entity->m_x * 32.0);
    m_y = Mth::floor(entity->m_y * 32.0);
    m_z = Mth::floor(entity->m_z * 32.0);
    m_type = (entity->isType(eLightningBolt));
}

int ClientboundAddGlobalEntityPacket::getEstimatedSize() {
    return 17;
}

EPacketType ClientboundAddGlobalEntityPacket::getPacketId() {
    return EPacketType::_ClientboundAddGlobalEntityPacket;
}

void ClientboundAddGlobalEntityPacket::read(DataInputStream* input) {
    m_id = input->readInt();
    m_type = input->readByte();
    m_x = input->readInt();
    m_y = input->readInt();
    m_z = input->readInt();
}

void ClientboundAddGlobalEntityPacket::write(DataOutputStream* output) {
    output->writeInt(m_id);
    output->writeByte(m_type);
    output->writeInt(m_x);
    output->writeInt(m_y);
    output->writeInt(m_z);
}

void ClientboundAddGlobalEntityPacket::handle(PacketListener* listener) {
    listener->handleAddGlobalEntity(shared_from_this());
}

int ClientboundAddGlobalEntityPacket::getId() {
    return m_id;
}

int ClientboundAddGlobalEntityPacket::getX() {
    return m_x;
}

int ClientboundAddGlobalEntityPacket::getY() {
    return m_y;
}

int ClientboundAddGlobalEntityPacket::getZ() {
    return m_z;
}

int ClientboundAddGlobalEntityPacket::getType() {
    return m_type;
}
