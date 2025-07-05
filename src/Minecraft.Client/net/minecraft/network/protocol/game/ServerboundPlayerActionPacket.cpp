#include "ServerboundPlayerActionPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPlayerActionPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerActionPacket());
}

ServerboundPlayerActionPacket::ServerboundPlayerActionPacket() {
    direction = 0;
    useTime = 0;
}

int ServerboundPlayerActionPacket::getEstimatedSize() {
    return 11;
}

EPacketType ServerboundPlayerActionPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerActionPacket;
}

void ServerboundPlayerActionPacket::read(DataInputStream* input) {
    action = input->readInt();
    pos = input->readBlockPos();
    direction = Direction::from3DDataValue(input->readUnsignedByte());
    useTime = input->readInt();
}

void ServerboundPlayerActionPacket::write(DataOutputStream* output) {
    output->writeInt(action);
    output->writeBlockPos(pos);
    output->writeByte(direction->get3DDataValue());
    output->writeInt(useTime);
}

void ServerboundPlayerActionPacket::handle(PacketListener* listener) {
    listener->handlePlayerAction(shared_from_this());
}

BlockPos ServerboundPlayerActionPacket::getPos() {
    return pos;
}

const Direction* ServerboundPlayerActionPacket::getDirection() {
    return direction;
}

int ServerboundPlayerActionPacket::getAction() {
    return action;
}

int ServerboundPlayerActionPacket::getUseTime() {
    return useTime;
}
