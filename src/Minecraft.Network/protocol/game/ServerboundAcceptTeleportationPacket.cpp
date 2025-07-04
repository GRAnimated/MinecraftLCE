#include "ServerboundAcceptTeleportationPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundAcceptTeleportationPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundAcceptTeleportationPacket());
}

ServerboundAcceptTeleportationPacket::ServerboundAcceptTeleportationPacket() {}

ServerboundAcceptTeleportationPacket::ServerboundAcceptTeleportationPacket(int id) {
    mId = id;
}

EPacketType ServerboundAcceptTeleportationPacket::getPacketId() {
    return EPacketType::_ServerboundAcceptTeleportationPacket;
}

void ServerboundAcceptTeleportationPacket::read(DataInputStream* input) {
    mId = input->readVarInt();
}

void ServerboundAcceptTeleportationPacket::write(DataOutputStream* output) {
    output->writeVarInt(mId);
}

void ServerboundAcceptTeleportationPacket::handle(PacketListener* listener) {
    listener->handleAcceptTeleportPacket(shared_from_this());
}

int ServerboundAcceptTeleportationPacket::getId() {
    return mId;
}
