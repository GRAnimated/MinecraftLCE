#include "ClientboundTakeItemEntityPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundTakeItemEntityPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundTakeItemEntityPacket());
}

ClientboundTakeItemEntityPacket::ClientboundTakeItemEntityPacket() {
    playerId = -1;
    itemId = -1;
    amount = -1;
}

EPacketType ClientboundTakeItemEntityPacket::getPacketId() {
    return EPacketType::_ClientboundTakeItemEntityPacket;
}

void ClientboundTakeItemEntityPacket::read(DataInputStream* input) {
    itemId = input->readVarInt();
    playerId = input->readVarInt();
    amount = input->readVarInt();
}

void ClientboundTakeItemEntityPacket::write(DataOutputStream* output) {
    output->writeVarInt(itemId);
    output->writeVarInt(playerId);
    output->writeVarInt(amount);
}

void ClientboundTakeItemEntityPacket::handle(PacketListener* listener) {
    listener->handleTakeItemEntity(shared_from_this());
}

int ClientboundTakeItemEntityPacket::getItemId() {
    return itemId;
}

int ClientboundTakeItemEntityPacket::getPlayerId() {
    return playerId;
}

int ClientboundTakeItemEntityPacket::getAmount() {
    return amount;
}
