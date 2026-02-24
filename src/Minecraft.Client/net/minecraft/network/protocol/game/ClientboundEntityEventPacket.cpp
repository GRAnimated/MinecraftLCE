#include "ClientboundEntityEventPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundEntityEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundEntityEventPacket());
}

ClientboundEntityEventPacket::ClientboundEntityEventPacket(std::shared_ptr<Entity> entity,
                                                           unsigned char eventId, int data) {
    m_entityId = entity->getId();
    m_eventId = eventId;
    m_data = data;
}

ClientboundEntityEventPacket::ClientboundEntityEventPacket() {
    m_entityId = 0;
    m_eventId = 0;
    m_data = 0;
}

int ClientboundEntityEventPacket::getEstimatedSize() {
    return 9;
}

EPacketType ClientboundEntityEventPacket::getPacketId() {
    return EPacketType::_ClientboundEntityEventPacket;
}

void ClientboundEntityEventPacket::read(DataInputStream* input) {
    m_entityId = input->readInt();
    m_eventId = input->readByte();
    m_data = input->readInt();
}

void ClientboundEntityEventPacket::write(DataOutputStream* output) {
    output->writeInt(m_entityId);
    output->writeByte(m_eventId);
    output->writeInt(m_data);
}

void ClientboundEntityEventPacket::handle(PacketListener* listener) {
    listener->handleEntityEvent(shared_from_this());
}

int ClientboundEntityEventPacket::getEntityId() {
    return m_entityId;
}

unsigned char ClientboundEntityEventPacket::getEventId() {
    return m_eventId;
}

int ClientboundEntityEventPacket::getData() {
    return m_data;
}
