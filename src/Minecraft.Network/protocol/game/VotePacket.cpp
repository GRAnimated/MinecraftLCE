#include "Minecraft.Network/protocol/game/VotePacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

VotePacket::VotePacket() : Packet() {}

std::shared_ptr<Packet> VotePacket::create() {
    return std::shared_ptr<Packet>(new VotePacket());
}

EPacketType VotePacket::getPacketId() {
    return EPacketType::_VotePacket;
}

void VotePacket::read(DataInputStream* input) {
    field_28 = input->readInt();
    field_2C = input->readByte();
    field_30 = input->readInt();
    field_34 = input->readInt();
}

void VotePacket::write(DataOutputStream* output) {
    output->writeInt(field_28);
    output->writeByte(field_2C);
    output->writeInt(field_30);
    output->writeInt(field_34);
}

void VotePacket::handle(PacketListener* listener) {
    listener->handleVote(shared_from_this());
}

int VotePacket::getEstimatedSize() {
    return 6;
}
