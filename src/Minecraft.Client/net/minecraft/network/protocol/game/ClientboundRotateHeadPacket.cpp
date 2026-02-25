#include "ClientboundRotateHeadPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include <memory>

std::shared_ptr<Packet> ClientboundRotateHeadPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundRotateHeadPacket());
}

ClientboundRotateHeadPacket::ClientboundRotateHeadPacket() {}

ClientboundRotateHeadPacket::ClientboundRotateHeadPacket(std::shared_ptr<Entity> entity,
                                                         unsigned char yHeadRot) {
    m_entityId = entity->getId();
    m_yHeadRot = yHeadRot;
}

int ClientboundRotateHeadPacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundRotateHeadPacket::getPacketId() {
    return EPacketType::_ClientboundRotateHeadPacket;
}

void ClientboundRotateHeadPacket::read(DataInputStream* input) {
    m_entityId = input->readVarInt();
    m_yHeadRot = input->readByte();
}

void ClientboundRotateHeadPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_entityId);
    output->writeByte(m_yHeadRot);
}

void ClientboundRotateHeadPacket::handle(PacketListener* listener) {
    listener->handleRotateMob(shared_from_this());
}

bool ClientboundRotateHeadPacket::canBeInvalidated() {
    return true;
}

bool ClientboundRotateHeadPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    auto otherPacket = std::dynamic_pointer_cast<ClientboundRotateHeadPacket>(packet);
    if (!otherPacket) {
        return false;
    }
    return m_entityId == otherPacket->m_entityId;
}

bool ClientboundRotateHeadPacket::isAync() {
    return true;
}

int ClientboundRotateHeadPacket::getEntityId() {
    return m_entityId;
}

unsigned char ClientboundRotateHeadPacket::getYHeadRot() {
    return m_yHeadRot;
}
