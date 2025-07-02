#include "ClientboundSetCarriedItemPacket.h"

#include "net/minecraft/core/io/DataInputStream.h"
#include "net/minecraft/core/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetCarriedItemPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetCarriedItemPacket());
}

ClientboundSetCarriedItemPacket::ClientboundSetCarriedItemPacket() {
    itemId = 0;
}

int ClientboundSetCarriedItemPacket::getEstimatedSize() {
    return 2;
}

EPacketType ClientboundSetCarriedItemPacket::getPacketId() {
    return EPacketType::_ClientboundSetCarriedItemPacket;
}

void ClientboundSetCarriedItemPacket::read(DataInputStream* input) {
    itemId = input->readByte();
}

void ClientboundSetCarriedItemPacket::write(DataOutputStream* output) {
    output->writeByte(itemId);
}

void ClientboundSetCarriedItemPacket::handle(PacketListener* listener) {
    listener->handleSetCarriedItem(shared_from_this());
}
