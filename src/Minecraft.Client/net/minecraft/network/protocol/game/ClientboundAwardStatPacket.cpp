#include "net/minecraft/network/protocol/game/ClientboundAwardStatPacket.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundAwardStatPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAwardStatPacket());
}

ClientboundAwardStatPacket::ClientboundAwardStatPacket() {}

ClientboundAwardStatPacket::ClientboundAwardStatPacket(int stat, int unk) {
    mStat = stat;
    mData = arrayWithLength<unsigned char>(4, true);
    int* data = (int*)mData.data;
    *data = unk;
}

ClientboundAwardStatPacket::~ClientboundAwardStatPacket() {
    if (mData.data) {
        delete[] mData.data;
        mData.data = nullptr;
    }
}

int ClientboundAwardStatPacket::getEstimatedSize() {
    return 6;
}

EPacketType ClientboundAwardStatPacket::getPacketId() {
    return EPacketType::_ClientboundAwardStatPacket;
}

void ClientboundAwardStatPacket::read(DataInputStream* input) {
    mStat = input->readInt();

    int size = input->readInt();
    if (size < 1)
        return;

    mData = arrayWithLength<unsigned char>(size, true);

    input->readFully(mData);
}

void ClientboundAwardStatPacket::write(DataOutputStream* output) {
    output->writeInt(mStat);
    output->writeInt(mData.length);
    if (mData.length > 0) {
        output->writeBytes(mData);
    }
}

void ClientboundAwardStatPacket::handle(PacketListener* listener) {
    listener->handleAwardStat(shared_from_this());
    mData.data = nullptr;
}

bool ClientboundAwardStatPacket::isAync() {
    return true;
}

arrayWithLength<unsigned char> ClientboundAwardStatPacket::getParamData() {
    return mData;
}
