#include "ClientboundAnimatePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/Entity.h"

std::shared_ptr<Packet> ClientboundAnimatePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAnimatePacket());
}

ClientboundAnimatePacket::ClientboundAnimatePacket() {
    mId = -1;
    mAction = 0;
}

ClientboundAnimatePacket::ClientboundAnimatePacket(std::shared_ptr<Entity> entity, int unk) {
    mId = entity->getId();
    mAction = unk;
}

int ClientboundAnimatePacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundAnimatePacket::getPacketId() {
    return EPacketType::_ClientboundAnimatePacket;
}

void ClientboundAnimatePacket::read(DataInputStream* input) {
    mId = input->readInt();
    mAction = input->readByte();
}

void ClientboundAnimatePacket::write(DataOutputStream* output) {
    output->writeInt(mId);
    output->writeByte(mAction);
}

void ClientboundAnimatePacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}

int ClientboundAnimatePacket::getId() {
    return mId;
}

int ClientboundAnimatePacket::getAction() {
    return mAction;
}
