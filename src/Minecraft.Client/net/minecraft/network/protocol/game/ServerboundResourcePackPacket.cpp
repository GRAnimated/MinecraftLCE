#include "ServerboundResourcePackPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundResourcePackPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundResourcePackPacket());
}

ServerboundResourcePackPacket::ServerboundResourcePackPacket() {}

EPacketType ServerboundResourcePackPacket::getPacketId() {
    return EPacketType::_ServerboundResourcePackPacket;
}

void ServerboundResourcePackPacket::read(DataInputStream* input) {
    m_resourcePackId = input->readInt();
}

void ServerboundResourcePackPacket::write(DataOutputStream* output) {
    output->writeInt(m_resourcePackId);
}

void ServerboundResourcePackPacket::handle(PacketListener* listener) {
    listener->handleResourcePackResponse(shared_from_this());
}
