#include "ClientboundBlockDestructionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundBlockDestructionPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundBlockDestructionPacket());
}

ClientboundBlockDestructionPacket::ClientboundBlockDestructionPacket() {
    mId = 0;
    mPos = BlockPos();
    mProgress = 0;
}

ClientboundBlockDestructionPacket::ClientboundBlockDestructionPacket(int id, const BlockPos& pos,
                                                                     int progress) {
    mId = id;
    mPos = pos;
    mProgress = progress;
}

int ClientboundBlockDestructionPacket::getEstimatedSize() {
    return 13;
}

EPacketType ClientboundBlockDestructionPacket::getPacketId() {
    return EPacketType::_ClientboundBlockDestructionPacket;
}

void ClientboundBlockDestructionPacket::read(DataInputStream* input) {
    mId = input->readInt();
    mPos = input->readBlockPos();
    mProgress = input->readUnsignedByte() & 0xFF;
}

void ClientboundBlockDestructionPacket::write(DataOutputStream* output) {
    output->writeInt(mId);
    output->writeBlockPos(mPos);
    output->writeByte(mProgress);
}

void ClientboundBlockDestructionPacket::handle(PacketListener* listener) {
    listener->handleBlockDestruction(shared_from_this());
}

int ClientboundBlockDestructionPacket::getId() {
    return mId;
}

BlockPos ClientboundBlockDestructionPacket::getPos() {
    return mPos;
}

int ClientboundBlockDestructionPacket::getProgress() {
    return mProgress;
}
