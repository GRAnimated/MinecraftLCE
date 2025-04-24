#include "Minecraft.World/Difficulty.h"
#include "Minecraft.Network/protocol/game/ClientboundChangeDifficultyPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundChangeDifficultyPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundChangeDifficultyPacket());
}

ClientboundChangeDifficultyPacket::ClientboundChangeDifficultyPacket() {}

EPacketType ClientboundChangeDifficultyPacket::getPacketId() {
    return EPacketType::_ClientboundChangeDifficultyPacket;
}

void ClientboundChangeDifficultyPacket::read(DataInputStream* input) {
    difficulty = Difficulty::byId(input->readUnsignedByte());
}

void ClientboundChangeDifficultyPacket::write(DataOutputStream* output) {
    output->writeByte(difficulty->getId());
}

void ClientboundChangeDifficultyPacket::handle(PacketListener* listener) {
    listener->handleChangeDifficulty(shared_from_this());
}
