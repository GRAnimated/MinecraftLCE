#include "Minecraft.Network/protocol/game/XZPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

XZPacket::XZPacket() : Packet() {}

XZPacket::XZPacket(char field_28, int x, int z) : Packet(), field_28(field_28), x(x), z(z) {}

void XZPacket::handle(PacketListener* listener) {
    listener->handleXZ(this->shared_from_this());
}

void XZPacket::read(DataInputStream* input) {
    field_28 = input->readChar();
    x = input->readInt();
    z = input->readInt();
}

void XZPacket::write(DataOutputStream* output) {
    output->writeChar(field_28);
    output->writeInt(x);
    output->writeInt(z);
}

int XZPacket::getEstimatedSize() {
    return 10;
}