#include "ClientboundContainerAckPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerAckPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerAckPacket());
}

ClientboundContainerAckPacket::ClientboundContainerAckPacket() {
    mContainerId = 0;
    mUid = 0;
    mAccepted = false;
}

ClientboundContainerAckPacket::ClientboundContainerAckPacket(int containerId, short uid, bool accepted) {
    mContainerId = containerId;
    mUid = uid;
    mAccepted = accepted;
}

int ClientboundContainerAckPacket::getEstimatedSize() {
    return 4;
}

EPacketType ClientboundContainerAckPacket::getPacketId() {
    return EPacketType::_ClientboundContainerAckPacket;
}

void ClientboundContainerAckPacket::read(DataInputStream* input) {
    mContainerId = static_cast<int>(input->readByte());
    mUid = input->readShort();
    mAccepted = input->readByte() != 0;
}

void ClientboundContainerAckPacket::write(DataOutputStream* output) {
    output->writeByte(mContainerId);
    output->writeShort(mUid);
    output->writeByte(static_cast<unsigned char>(mAccepted));
}

void ClientboundContainerAckPacket::handle(PacketListener* listener) {
    listener->handleContainerAck(shared_from_this());
}

int ClientboundContainerAckPacket::getContainerId() {
    return mContainerId;
}

short ClientboundContainerAckPacket::getUid() {
    return mUid;
}

bool ClientboundContainerAckPacket::isAccepted() {
    return mAccepted;
}
