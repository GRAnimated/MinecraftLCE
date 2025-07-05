#include "ClientboundGameEventPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundGameEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundGameEventPacket());
}

ClientboundGameEventPacket::ClientboundGameEventPacket() {
    mEvent = 0;
    mParam = 0.0;
    mPlayerIndex = -1;
}

int ClientboundGameEventPacket::getEstimatedSize() {
    return 3;
}

EPacketType ClientboundGameEventPacket::getPacketId() {
    return EPacketType::_ClientboundGameEventPacket;
}

void ClientboundGameEventPacket::read(DataInputStream* input) {
    mEvent = static_cast<int>(input->readUnsignedByte());
    mParam = input->readFloat();
    mPlayerIndex = input->readInt();
}

void ClientboundGameEventPacket::write(DataOutputStream* output) {
    output->writeByte(mEvent);
    output->writeFloat(mParam);
    output->writeInt(mPlayerIndex);
}

void ClientboundGameEventPacket::handle(PacketListener* listener) {
    listener->handleGameEvent(shared_from_this());
}

int ClientboundGameEventPacket::getEvent() {
    return mEvent;
}

float ClientboundGameEventPacket::getParam() {
    return mParam;
}

int ClientboundGameEventPacket::getPlayerIndex() {
    return mPlayerIndex;
}
