#include "ClientboundLevelEventPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundLevelEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundLevelEventPacket());
}

ClientboundLevelEventPacket::ClientboundLevelEventPacket() {
    type = 0;
    data = 0;
    pos = BlockPos::BlockPos();
}

int ClientboundLevelEventPacket::getEstimatedSize() {
    return 21;
}

EPacketType ClientboundLevelEventPacket::getPacketId() {
    return EPacketType::_ClientboundLevelEventPacket;
}

void ClientboundLevelEventPacket::read(DataInputStream* input) {
    type = input->readInt();
    pos = input->readBlockPos();
    data = input->readInt();
    globalEvent = input->readBoolean();
}

void ClientboundLevelEventPacket::write(DataOutputStream* output) {
    output->writeInt(type);
    output->writeBlockPos(pos);
    output->writeInt(data);
    output->writeBoolean(globalEvent);
}

void ClientboundLevelEventPacket::handle(PacketListener* listener) {
    listener->handleLevelEvent(shared_from_this());
}

int ClientboundLevelEventPacket::getType() {
    return type;
}

int ClientboundLevelEventPacket::getData() {
    return data;
}

BlockPos ClientboundLevelEventPacket::getPos() {
    return pos;
}

bool ClientboundLevelEventPacket::isGlobalEvent() {
    return globalEvent;
}
