#include "ServerboundSetCarriedItemPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundSetCarriedItemPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundSetCarriedItemPacket());
}

ServerboundSetCarriedItemPacket::ServerboundSetCarriedItemPacket() : Packet() {}

ServerboundSetCarriedItemPacket::ServerboundSetCarriedItemPacket(int carriedItem) : Packet() {
    m_carriedItem = carriedItem;
}

EPacketType ServerboundSetCarriedItemPacket::getPacketId() {
    return EPacketType::_ServerboundSetCarriedItemPacket;
}

void ServerboundSetCarriedItemPacket::read(DataInputStream* input) {
    m_carriedItem = input->readShort();
}

void ServerboundSetCarriedItemPacket::write(DataOutputStream* output) {
    output->writeShort(m_carriedItem);
}

void ServerboundSetCarriedItemPacket::handle(PacketListener* listener) {
    listener->handleSetCarriedItem(shared_from_this());
}

int ServerboundSetCarriedItemPacket::getCarriedItem() {
    return m_carriedItem;
}
