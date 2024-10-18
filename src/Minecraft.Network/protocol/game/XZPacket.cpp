#include "Minecraft.Network/protocol/game/XZPacket.h"

#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> XZPacket::create() {
    return std::shared_ptr<Packet>(new XZPacket());
}

XZPacket::XZPacket() : Packet() {}

XZPacket::XZPacket(char field_28, int x, int z) : Packet(), field_28(field_28), mX(x), mZ(z) {}

EPacketType XZPacket::getPacketId() {
    return EPacketType::_XZPacket;
}

void XZPacket::read(DataInputStream* input) {
    field_28 = input->readChar();
    mX = input->readInt();
    mZ = input->readInt();
}

void XZPacket::write(DataOutputStream* output) {
    output->writeChar(field_28);
    output->writeInt(mX);
    output->writeInt(mZ);
}

void XZPacket::handle(PacketListener* listener) {
    listener->handleXZ(this->shared_from_this());
}

int XZPacket::getEstimatedSize() {
    return 10;
}
