#include "net/minecraft/network/protocol/game/ClientboundChangeDifficultyPacket.h"
#include "net/minecraft/world/Difficulty.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundChangeDifficultyPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundChangeDifficultyPacket());
}

ClientboundChangeDifficultyPacket::ClientboundChangeDifficultyPacket() {}

EPacketType ClientboundChangeDifficultyPacket::getPacketId() {
    return EPacketType::_ClientboundChangeDifficultyPacket;
}

void ClientboundChangeDifficultyPacket::read(DataInputStream* input) {
    m_difficulty = Difficulty::byId(input->readUnsignedByte());
}

void ClientboundChangeDifficultyPacket::write(DataOutputStream* output) {
    output->writeByte(m_difficulty->getId());
}

void ClientboundChangeDifficultyPacket::handle(PacketListener* listener) {
    listener->handleChangeDifficulty(shared_from_this());
}
