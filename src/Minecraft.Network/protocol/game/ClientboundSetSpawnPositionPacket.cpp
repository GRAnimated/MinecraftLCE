#include "Minecraft.Network/protocol/game/ClientboundSetSpawnPositionPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetSpawnPositionPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetSpawnPositionPacket());
}

ClientboundSetSpawnPositionPacket::ClientboundSetSpawnPositionPacket() : Packet() {
    mPos = BlockPos();
}

void ClientboundSetSpawnPositionPacket::handle(PacketListener* listener) {
    listener->handleSetSpawn(this->shared_from_this());
}

void ClientboundSetSpawnPositionPacket::read(DataInputStream* input) {
    mPos = input->readBlockPos();
}

void ClientboundSetSpawnPositionPacket::write(DataOutputStream* output) {
    output->writeBlockPos(mPos);
}

int ClientboundSetSpawnPositionPacket::getEstimatedSize() {
    return 12;
}

bool ClientboundSetSpawnPositionPacket::canBeInvalidated() {
    return true;
}

bool ClientboundSetSpawnPositionPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

bool ClientboundSetSpawnPositionPacket::isAync() {
    return false;
}

EPacketType ClientboundSetSpawnPositionPacket::getPacketId() {
    return EPacketType::_ClientboundSetSpawnPositionPacket;
}
