#include "ClientboundEntityEventPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundEntityEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundEntityEventPacket());
}

ClientboundEntityEventPacket::ClientboundEntityEventPacket(std::shared_ptr<Entity> entity,
                                                           unsigned char eventId, int data) {
    mEntityId = entity->getId();
    mEventId = eventId;
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
