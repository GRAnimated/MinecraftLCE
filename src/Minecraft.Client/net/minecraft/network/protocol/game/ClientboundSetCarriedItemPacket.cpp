#include "ClientboundSetCarriedItemPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetCarriedItemPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetCarriedItemPacket());
}

ClientboundSetCarriedItemPacket::ClientboundSetCarriedItemPacket() {
    m_itemId = 0;
}

int ClientboundSetCarriedItemPacket::getEstimatedSize() {
    return 2;
}

EPacketType ClientboundSetCarriedItemPacket::getPacketId() {
    return EPacketType::_ClientboundSetCarriedItemPacket;
}

void ClientboundSetCarriedItemPacket::read(DataInputStream* input) {
    m_itemId = input->readByte();
}

void ClientboundSetCarriedItemPacket::write(DataOutputStream* output) {
    output->writeByte(m_itemId);
}

void ClientboundSetCarriedItemPacket::handle(PacketListener* listener) {
    listener->handleSetCarriedItem(shared_from_this());
}
