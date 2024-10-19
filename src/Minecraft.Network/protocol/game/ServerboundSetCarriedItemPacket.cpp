#include "Minecraft.Network/protocol/game/ServerboundSetCarriedItemPacket.h"

#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ServerboundSetCarriedItemPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundSetCarriedItemPacket());
}

ServerboundSetCarriedItemPacket::ServerboundSetCarriedItemPacket() : Packet() {}

ServerboundSetCarriedItemPacket::ServerboundSetCarriedItemPacket(int carriedItem) : Packet() {
    mCarriedItem = carriedItem;
}

EPacketType ServerboundSetCarriedItemPacket::getPacketId() {
    return EPacketType::_ServerboundSetCarriedItemPacket;
}

void ServerboundSetCarriedItemPacket::read(DataInputStream* input) {
    mCarriedItem = input->readShort();
}

void ServerboundSetCarriedItemPacket::write(DataOutputStream* output) {
    output->writeShort(mCarriedItem);
}

void ServerboundSetCarriedItemPacket::handle(PacketListener* listener) {
    listener->handleSetCarriedItem(shared_from_this());
}

int ServerboundSetCarriedItemPacket::getCarriedItem() {
    return mCarriedItem;
}
