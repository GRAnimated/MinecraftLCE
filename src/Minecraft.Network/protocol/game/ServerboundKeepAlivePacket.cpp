#include "ServerboundKeepAlivePacket.h"

#include "../../../Minecraft.Core/io/DataInputStream.h"
#include "../../../Minecraft.Core/io/DataOutputStream.h"
#include "../../PacketListener.h"

std::shared_ptr<Packet> ServerboundKeepAlivePacket::create() {
    return std::shared_ptr<Packet>(new ServerboundKeepAlivePacket());
}

ServerboundKeepAlivePacket::ServerboundKeepAlivePacket() : Packet() {
    mId = 0;
}

void ServerboundKeepAlivePacket::handle(PacketListener* listener) {
    listener->handleKeepAlive(shared_from_this());
}

void ServerboundKeepAlivePacket::read(DataInputStream* input) {
    mId = input->readVarInt();
}

void ServerboundKeepAlivePacket::write(DataOutputStream* output) {
    output->writeVarInt(mId);
}

EPacketType ServerboundKeepAlivePacket::getPacketId() {
    return EPacketType::_ServerboundKeepAlivePacket;
}
