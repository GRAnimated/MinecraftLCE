#include "ClientboundRotateHeadPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"
#include <memory>

std::shared_ptr<Packet> ClientboundRotateHeadPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundRotateHeadPacket());
}

ClientboundRotateHeadPacket::ClientboundRotateHeadPacket() {}

ClientboundRotateHeadPacket::ClientboundRotateHeadPacket(std::shared_ptr<Entity> entity,
                                                         unsigned char yHeadRot) {
    entityId = entity->getId();
    mYHeadRot = yHeadRot;
}

int ClientboundRotateHeadPacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundRotateHeadPacket::getPacketId() {
    return EPacketType::_ClientboundRotateHeadPacket;
}

void ClientboundRotateHeadPacket::read(DataInputStream* input) {
    entityId = input->readVarInt();
    mYHeadRot = input->readByte();
}

void ClientboundRotateHeadPacket::write(DataOutputStream* output) {
    output->writeVarInt(entityId);
    output->writeByte(mYHeadRot);
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
    return entityId == otherPacket->entityId;
}

bool ClientboundRotateHeadPacket::isAync() {
    return true;
}

int ClientboundRotateHeadPacket::getEntityId() {
    return entityId;
}

unsigned char ClientboundRotateHeadPacket::getYHeadRot() {
    return mYHeadRot;
}
