#include "DebugOptionsPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> DebugOptionsPacket::create() {
    return std::shared_ptr<Packet>(new DebugOptionsPacket());
}

DebugOptionsPacket::DebugOptionsPacket() {
    dword18 = 0;
}

DebugOptionsPacket::DebugOptionsPacket(unsigned int unk1) {
    dword18 = unk1;
}

int DebugOptionsPacket::getEstimatedSize() {
    return 4;
}

EPacketType DebugOptionsPacket::getPacketId() {
    return EPacketType::_DebugOptionsPacket;
}

void DebugOptionsPacket::read(DataInputStream* input) {
    dword18 = input->readInt();
}

void DebugOptionsPacket::write(DataOutputStream* output) {
    output->writeInt(dword18);
}

void DebugOptionsPacket::handle(PacketListener* listener) {
    listener->handleDebugOptions(shared_from_this());
}
