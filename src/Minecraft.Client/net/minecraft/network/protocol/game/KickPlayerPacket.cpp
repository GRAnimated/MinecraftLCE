#include "KickPlayerPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> KickPlayerPacket::create() {
    return std::shared_ptr<Packet>(new KickPlayerPacket());
}

KickPlayerPacket::KickPlayerPacket() {
    byte18 = 0;
}

KickPlayerPacket::KickPlayerPacket(unsigned char unk1) {
    byte18 = unk1;
}

int KickPlayerPacket::getEstimatedSize() {
    return 1;
}

EPacketType KickPlayerPacket::getPacketId() {
    return EPacketType::_KickPlayerPacket;
}

void KickPlayerPacket::read(DataInputStream* input) {
    byte18 = input->readByte();
}

void KickPlayerPacket::write(DataOutputStream* output) {
    output->writeByte(byte18);
}

void KickPlayerPacket::handle(PacketListener* listener) {
    listener->handleKickPlayer(shared_from_this());
}
