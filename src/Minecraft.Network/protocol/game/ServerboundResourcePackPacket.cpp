#include "Minecraft.Network/protocol/game/ServerboundResourcePackPacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ServerboundResourcePackPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundResourcePackPacket());
}

ServerboundResourcePackPacket::ServerboundResourcePackPacket() {}

EPacketType ServerboundResourcePackPacket::getPacketId() {
    return EPacketType::_ServerboundResourcePackPacket;
}

void ServerboundResourcePackPacket::read(DataInputStream* input) {
    resourcePackId = input->readInt();
}

void ServerboundResourcePackPacket::write(DataOutputStream* output) {
    output->writeInt(resourcePackId);
}

void ServerboundResourcePackPacket::handle(PacketListener* listener) {
    listener->handleResourcePackResponse(shared_from_this());
}
