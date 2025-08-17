#include "net/minecraft/network/protocol/game/DisconnectPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> DisconnectPacket::create() {
    return std::shared_ptr<Packet>(new DisconnectPacket());
}

DisconnectPacket::DisconnectPacket() : Packet() {
    mReason = eDisconnectReason::_0;
}

DisconnectPacket::DisconnectPacket(eDisconnectReason reason) : Packet() {
    mReason = reason;
}

void DisconnectPacket::handle(PacketListener* listener) {
    listener->handleDisconnect(shared_from_this());
}

void DisconnectPacket::read(DataInputStream* input) {
    mReason = static_cast<eDisconnectReason>(input->readInt());
}

void DisconnectPacket::write(DataOutputStream* output) {
    output->writeInt(static_cast<int>(mReason));
}

EPacketType DisconnectPacket::getPacketId() {
    return EPacketType::_DisconnectPacket;
}

int DisconnectPacket::getEstimatedSize() {
    return 4;
}

bool DisconnectPacket::canBeInvalidated() {
    return true;
}

bool DisconnectPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}
