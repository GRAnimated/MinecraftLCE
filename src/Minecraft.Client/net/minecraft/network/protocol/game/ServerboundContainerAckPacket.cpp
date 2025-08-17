#include "ServerboundContainerAckPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundContainerAckPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundContainerAckPacket());
}

ServerboundContainerAckPacket::ServerboundContainerAckPacket() {}

ServerboundContainerAckPacket::ServerboundContainerAckPacket(int containerId, short uid, bool accepted) {
    mContainerId = containerId;
    mUid = uid;
    mAccepted = accepted;
}

EPacketType ServerboundContainerAckPacket::getPacketId() {
    return EPacketType::_ServerboundContainerAckPacket;
}

void ServerboundContainerAckPacket::read(DataInputStream* input) {
    mContainerId = static_cast<int>(input->readByte());
    mUid = input->readShort();
    mAccepted = input->readBoolean();
}

void ServerboundContainerAckPacket::write(DataOutputStream* output) {
    output->writeByte(mContainerId);
    output->writeShort(mUid);
    output->writeBoolean(mAccepted);
}

void ServerboundContainerAckPacket::handle(PacketListener* listener) {
    listener->handleContainerAck(shared_from_this());
}

int ServerboundContainerAckPacket::getContainerId() {
    return mContainerId;
}

short ServerboundContainerAckPacket::getUid() {
    return mUid;
}
