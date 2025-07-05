#include "ClientboundBlockDestructionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundBlockDestructionPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundBlockDestructionPacket());
}

ClientboundBlockDestructionPacket::ClientboundBlockDestructionPacket() {
    id = 0;
    pos = BlockPos::BlockPos();
    progress = 0;
}

int ClientboundBlockDestructionPacket::getEstimatedSize() {
    return 13;
}

EPacketType ClientboundBlockDestructionPacket::getPacketId() {
    return EPacketType::_ClientboundBlockDestructionPacket;
}

void ClientboundBlockDestructionPacket::read(DataInputStream* input) {
    id = input->readInt();
    pos = input->readBlockPos();
    progress = input->readUnsignedByte() & 0xFF;
}

void ClientboundBlockDestructionPacket::write(DataOutputStream* output) {
    output->writeInt(id);
    output->writeBlockPos(pos);
    output->writeByte(progress);
}

void ClientboundBlockDestructionPacket::handle(PacketListener* listener) {
    listener->handleBlockDestruction(shared_from_this());
}

int ClientboundBlockDestructionPacket::getId() {
    return id;
}

BlockPos ClientboundBlockDestructionPacket::getPos() {
    return pos;
}

int ClientboundBlockDestructionPacket::getProgress() {
    return progress;
}
