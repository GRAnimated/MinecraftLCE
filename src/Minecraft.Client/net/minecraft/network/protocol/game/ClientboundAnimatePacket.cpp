#include "ClientboundAnimatePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/Entity.h"

std::shared_ptr<Packet> ClientboundAnimatePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAnimatePacket());
}

ClientboundAnimatePacket::ClientboundAnimatePacket() {
    m_id = -1;
    m_action = 0;
}

ClientboundAnimatePacket::ClientboundAnimatePacket(std::shared_ptr<Entity> entity, int unk) {
    m_id = entity->getId();
    m_action = unk;
}

int ClientboundAnimatePacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundAnimatePacket::getPacketId() {
    return EPacketType::_ClientboundAnimatePacket;
}

void ClientboundAnimatePacket::read(DataInputStream* input) {
    m_id = input->readInt();
    m_action = input->readByte();
}

void ClientboundAnimatePacket::write(DataOutputStream* output) {
    output->writeInt(m_id);
    output->writeByte(m_action);
}

void ClientboundAnimatePacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}

int ClientboundAnimatePacket::getId() {
    return m_id;
}

int ClientboundAnimatePacket::getAction() {
    return m_action;
}
