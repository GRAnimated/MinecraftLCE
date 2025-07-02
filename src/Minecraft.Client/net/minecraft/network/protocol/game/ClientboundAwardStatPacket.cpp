#include "net/minecraft/network/protocol/game/ClientboundAwardStatPacket.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundAwardStatPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAwardStatPacket());
}

ClientboundAwardStatPacket::ClientboundAwardStatPacket() {}

ClientboundAwardStatPacket::~ClientboundAwardStatPacket() {
    if (data.data) {
        delete[] data.data;
        data.data = nullptr;
    }
}

int ClientboundAwardStatPacket::getEstimatedSize() {
    return 6;
}

EPacketType ClientboundAwardStatPacket::getPacketId() {
    return EPacketType::_ClientboundAwardStatPacket;
}

void ClientboundAwardStatPacket::read(DataInputStream* input) {
    stat = input->readInt();

    int size = input->readInt();
    if (size < 1)
        return;

    data = arrayWithLength<unsigned char>(size, true);

    input->readFully(data);
}

void ClientboundAwardStatPacket::write(DataOutputStream* output) {
    output->writeInt(stat);
    output->writeInt(data.length);
    if (data.length > 0) {
        output->writeBytes(data);
    }
}

void ClientboundAwardStatPacket::handle(PacketListener* listener) {
    listener->handleAwardStat(shared_from_this());
    data.data = nullptr;
}

bool ClientboundAwardStatPacket::isAync() {
    return true;
}
