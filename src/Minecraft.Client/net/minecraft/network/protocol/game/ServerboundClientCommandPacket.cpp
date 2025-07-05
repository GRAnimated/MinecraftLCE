#include "ServerboundClientCommandPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include <memory>

std::shared_ptr<Packet> ServerboundClientCommandPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundClientCommandPacket());
}

ServerboundClientCommandPacket::ServerboundClientCommandPacket() {
    commandId = 0;
}

int ServerboundClientCommandPacket::getEstimatedSize() {
    return 1;
}

EPacketType ServerboundClientCommandPacket::getPacketId() {
    return EPacketType::_ServerboundClientCommandPacket;
}

void ServerboundClientCommandPacket::read(DataInputStream* input) {
    commandId = input->readInt();
}

void ServerboundClientCommandPacket::write(DataOutputStream* output) {
    output->writeInt(commandId);
}

// why does this one make a dynamic cast?
void ServerboundClientCommandPacket::handle(PacketListener* listener) {
    listener->handleClientCommand(
        std::dynamic_pointer_cast<ServerboundClientCommandPacket>(shared_from_this()));
}
