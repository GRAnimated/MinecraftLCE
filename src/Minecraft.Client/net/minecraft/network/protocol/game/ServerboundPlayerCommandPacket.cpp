#include "net/minecraft/network/protocol/game/ServerboundPlayerCommandPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPlayerCommandPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerCommandPacket());
}

ServerboundPlayerCommandPacket::ServerboundPlayerCommandPacket() {
    m_action = 0;
    m_data = 0;
    m_id = -1;
}

int ServerboundPlayerCommandPacket::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundPlayerCommandPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerCommandPacket;
}

void ServerboundPlayerCommandPacket::read(DataInputStream* input) {
    m_id = input->readVarInt();
    m_action = input->readInt();
    m_data = input->readVarInt();
}

void ServerboundPlayerCommandPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_id);
    output->writeInt(m_action);
    output->writeVarInt(m_data);
}

void ServerboundPlayerCommandPacket::handle(PacketListener* listener) {
    listener->handlePlayerCommand(shared_from_this());
}

int ServerboundPlayerCommandPacket::getAction() {
    return m_action;
}

int ServerboundPlayerCommandPacket::getData() {
    return m_data;
}
