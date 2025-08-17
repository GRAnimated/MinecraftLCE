#include "ClientboundSetSpawnPositionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetSpawnPositionPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetSpawnPositionPacket());
}

ClientboundSetSpawnPositionPacket::ClientboundSetSpawnPositionPacket() : Packet() {
    mPos = BlockPos();
}

ClientboundSetSpawnPositionPacket::ClientboundSetSpawnPositionPacket(int x, int y, int z) : Packet() {
    mPos = BlockPos(x, y, z);
}

ClientboundSetSpawnPositionPacket::ClientboundSetSpawnPositionPacket(const BlockPos& pos) : Packet() {
    mPos = pos;
}

EPacketType ClientboundSetSpawnPositionPacket::getPacketId() {
    return EPacketType::_ClientboundSetSpawnPositionPacket;
}

void ClientboundSetSpawnPositionPacket::read(DataInputStream* input) {
    mPos = input->readBlockPos();
}

void ClientboundSetSpawnPositionPacket::write(DataOutputStream* output) {
    output->writeBlockPos(mPos);
}

void ClientboundSetSpawnPositionPacket::handle(PacketListener* listener) {
    listener->handleSetSpawn(shared_from_this());
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
