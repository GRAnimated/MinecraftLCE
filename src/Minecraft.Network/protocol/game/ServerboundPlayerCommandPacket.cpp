#include "ServerboundPlayerCommandPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPlayerCommandPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerCommandPacket());
}

ServerboundPlayerCommandPacket::ServerboundPlayerCommandPacket() {
    action = 0;
    data = 0;
    id = -1;
}

int ServerboundPlayerCommandPacket::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundPlayerCommandPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerCommandPacket;
}

void ServerboundPlayerCommandPacket::read(DataInputStream* input) {
    id = input->readVarInt();
    action = input->readInt();
    data = input->readVarInt();
}

void ServerboundPlayerCommandPacket::write(DataOutputStream* output) {
    output->writeVarInt(id);
    output->writeInt(action);
    output->writeVarInt(data);
}

void ServerboundPlayerCommandPacket::handle(PacketListener* listener) {
    listener->handlePlayerCommand(shared_from_this());
}

int ServerboundPlayerCommandPacket::getAction() {
    return action;
}

int ServerboundPlayerCommandPacket::getData() {
    return data;
}
