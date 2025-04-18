#include "Minecraft.Network/protocol/game/ClientboundSetCarriedItemPacket.h"

#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

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
