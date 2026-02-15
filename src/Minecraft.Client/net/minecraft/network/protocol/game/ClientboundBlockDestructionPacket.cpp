#include "ClientboundBlockDestructionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundBlockDestructionPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundBlockDestructionPacket());
}

ClientboundBlockDestructionPacket::ClientboundBlockDestructionPacket() {
    m_id = 0;
    m_pos = BlockPos();
    m_progress = 0;
}

ClientboundBlockDestructionPacket::ClientboundBlockDestructionPacket(int id, const BlockPos& pos,
                                                                     int progress) {
    m_id = id;
    m_pos = pos;
    m_progress = progress;
}

int ClientboundBlockDestructionPacket::getEstimatedSize() {
    return 13;
}

EPacketType ClientboundBlockDestructionPacket::getPacketId() {
    return EPacketType::_ClientboundBlockDestructionPacket;
}

void ClientboundBlockDestructionPacket::read(DataInputStream* input) {
    m_id = input->readInt();
    m_pos = input->readBlockPos();
    m_progress = input->readUnsignedByte() & 0xFF;
}

void ClientboundBlockDestructionPacket::write(DataOutputStream* output) {
    output->writeInt(m_id);
    output->writeBlockPos(m_pos);
    output->writeByte(m_progress);
}

void ClientboundBlockDestructionPacket::handle(PacketListener* listener) {
    listener->handleBlockDestruction(shared_from_this());
}

int ClientboundBlockDestructionPacket::getId() {
    return m_id;
}

BlockPos ClientboundBlockDestructionPacket::getPos() {
    return m_pos;
}

int ClientboundBlockDestructionPacket::getProgress() {
    return m_progress;
}
