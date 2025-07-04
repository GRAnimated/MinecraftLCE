#include "ClientboundEntityEventPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundEntityEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundEntityEventPacket());
}

ClientboundEntityEventPacket::ClientboundEntityEventPacket(std::shared_ptr<Entity> entity, unsigned char eventId, int data) {
    mEventId = eventId;
    mEntityId = entity->getId();
    mData = data;
}

ClientboundEntityEventPacket::ClientboundEntityEventPacket() {
    mEntityId = 0;
    mEventId = 0;
    mData = 0;
}

int ClientboundEntityEventPacket::getEstimatedSize() {
    return 9;
}

EPacketType ClientboundEntityEventPacket::getPacketId() {
    return EPacketType::_ClientboundEntityEventPacket;
}

void ClientboundEntityEventPacket::read(DataInputStream* input) {
    mEntityId = input->readInt();
    mEventId = input->readByte();
    mData = input->readInt();
}

void ClientboundEntityEventPacket::write(DataOutputStream* output) {
    output->writeInt(mEntityId);
    output->writeByte(mEventId);
    output->writeInt(mData);
}

void ClientboundEntityEventPacket::handle(PacketListener* listener) {
    listener->handleEntityEvent(shared_from_this());
}

int ClientboundEntityEventPacket::getEntityId() {
    return mEntityId;
}

unsigned char ClientboundEntityEventPacket::getEventId() {
    return mEventId;
}

int ClientboundEntityEventPacket::getData() {
    return mData;
}
