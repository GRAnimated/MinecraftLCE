#include "net/minecraft/network/protocol/game/VotePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

VotePacket::VotePacket() : Packet() {}

std::shared_ptr<Packet> VotePacket::create() {
    return std::shared_ptr<Packet>(new VotePacket());
}

EPacketType VotePacket::getPacketId() {
    return EPacketType::_VotePacket;
}

void VotePacket::read(DataInputStream* input) {
    m_field28 = input->readInt();
    m_field2C = input->readByte();
    m_field30 = input->readInt();
    m_field34 = input->readInt();
}

void VotePacket::write(DataOutputStream* output) {
    output->writeInt(m_field28);
    output->writeByte(m_field2C);
    output->writeInt(m_field30);
    output->writeInt(m_field34);
}

void VotePacket::handle(PacketListener* listener) {
    listener->handleVote(shared_from_this());
}

int VotePacket::getEstimatedSize() {
    return 6;
}
