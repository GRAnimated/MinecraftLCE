#include "ClientboundKeepAlivePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundKeepAlivePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundKeepAlivePacket());
}

ClientboundKeepAlivePacket::ClientboundKeepAlivePacket() : Packet() {
    mId = 0;
}

void ClientboundKeepAlivePacket::handle(PacketListener* listener) {
    listener->handleKeepAlive(shared_from_this());
}

void ClientboundKeepAlivePacket::read(DataInputStream* input) {
    mId = input->readInt();
}

void ClientboundKeepAlivePacket::write(DataOutputStream* output) {
    output->writeInt(mId);
}

EPacketType ClientboundKeepAlivePacket::getPacketId() {
    return EPacketType::_ClientboundKeepAlivePacket;
}

int ClientboundKeepAlivePacket::getEstimatedSize() {
    return 4;
}

bool ClientboundKeepAlivePacket::canBeInvalidated() {
    return true;
}

bool ClientboundKeepAlivePacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

bool ClientboundKeepAlivePacket::isAync() {
    return true;
}
