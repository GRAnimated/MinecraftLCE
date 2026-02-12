#include "net/minecraft/network/protocol/game/ServerboundPlayerActionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPlayerActionPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerActionPacket());
}

ServerboundPlayerActionPacket::ServerboundPlayerActionPacket() {
    m_direction = 0;
    m_useTime = 0;
}

int ServerboundPlayerActionPacket::getEstimatedSize() {
    return 11;
}

EPacketType ServerboundPlayerActionPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerActionPacket;
}

void ServerboundPlayerActionPacket::read(DataInputStream* input) {
    m_action = input->readInt();
    m_pos = input->readBlockPos();
    m_direction = Direction::from3DDataValue(input->readUnsignedByte());
    m_useTime = input->readInt();
}

void ServerboundPlayerActionPacket::write(DataOutputStream* output) {
    output->writeInt(m_action);
    output->writeBlockPos(m_pos);
    output->writeByte(m_direction->get3DDataValue());
    output->writeInt(m_useTime);
}

void ServerboundPlayerActionPacket::handle(PacketListener* listener) {
    listener->handlePlayerAction(shared_from_this());
}

BlockPos ServerboundPlayerActionPacket::getPos() {
    return m_pos;
}

const Direction* ServerboundPlayerActionPacket::getDirection() {
    return m_direction;
}

int ServerboundPlayerActionPacket::getAction() {
    return m_action;
}

int ServerboundPlayerActionPacket::getUseTime() {
    return m_useTime;
}
