#include "ServerboundAcceptTeleportationPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundAcceptTeleportationPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundAcceptTeleportationPacket());
}

ServerboundAcceptTeleportationPacket::ServerboundAcceptTeleportationPacket() {}

ServerboundAcceptTeleportationPacket::ServerboundAcceptTeleportationPacket(int id) {
    m_id = id;
}

EPacketType ServerboundAcceptTeleportationPacket::getPacketId() {
    return EPacketType::_ServerboundAcceptTeleportationPacket;
}

void ServerboundAcceptTeleportationPacket::read(DataInputStream* input) {
    m_id = input->readVarInt();
}

void ServerboundAcceptTeleportationPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_id);
}

void ServerboundAcceptTeleportationPacket::handle(PacketListener* listener) {
    listener->handleAcceptTeleportPacket(shared_from_this());
}

int ServerboundAcceptTeleportationPacket::getId() {
    return m_id;
}
