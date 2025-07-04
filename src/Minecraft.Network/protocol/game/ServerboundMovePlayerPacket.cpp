#include "ServerboundMovePlayerPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundMovePlayerPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundMovePlayerPacket());
}

ServerboundMovePlayerPacket::ServerboundMovePlayerPacket() {
    mX = 0.0;
    mY = 0.0;
    mZ = 0.0;
    mYRot = 0.0;
    mXRot = 0.0;
    hasRot = false;
    hasPos = false;
    onGround = false;
    bool3B = false;
}

int ServerboundMovePlayerPacket::getEstimatedSize() {
    return 1;
}

EPacketType ServerboundMovePlayerPacket::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPacket;
}

void ServerboundMovePlayerPacket::read(DataInputStream* input) {
    int8_t flags = static_cast<int8_t>(input->readByte());
    onGround = flags & 1;
    bool3B = (flags >> 1) & 1;
}

void ServerboundMovePlayerPacket::write(DataOutputStream* output) {
    uint8_t fOnGround = static_cast<uint8_t>(onGround);
    uint8_t fBool3B = static_cast<uint8_t>(bool3B) << 1;
    uint8_t flags = fOnGround | fBool3B;
    output->writeByte(flags);
}

void ServerboundMovePlayerPacket::handle(PacketListener* listener) {
    listener->handleMovePlayer(shared_from_this());
}

double ServerboundMovePlayerPacket::getX(double x) {
    return hasPos ? mX : x;
}

double ServerboundMovePlayerPacket::getY(double y) {
    return hasPos ? mY : y;
}

double ServerboundMovePlayerPacket::getZ(double z) {
    return hasPos ? mZ : z;
}

float ServerboundMovePlayerPacket::getYRot(float yRot) {
    return hasRot ? mYRot : yRot;
}

float ServerboundMovePlayerPacket::getXRot(float xRot) {
    return hasRot ? mXRot : xRot;
}

bool ServerboundMovePlayerPacket::isOnGround() {
    return onGround;
}

ServerboundMovePlayerPacket::Pos::Pos() {
    hasPos = true;
}

int ServerboundMovePlayerPacket::Pos::getEstimatedSize() {
    return 33;
}

EPacketType ServerboundMovePlayerPacket::Pos::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPosPacket;
}

void ServerboundMovePlayerPacket::Pos::read(DataInputStream* input) {
    mX = input->readDouble();
    mY = input->readDouble();
    mZ = input->readDouble();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::Pos::write(DataOutputStream* output) {
    output->writeDouble(mX);
    output->writeDouble(mY);
    output->writeDouble(mZ);
    ServerboundMovePlayerPacket::write(output);
}

ServerboundMovePlayerPacket::Rot::Rot() {
    hasRot = true;
}

int ServerboundMovePlayerPacket::Rot::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundMovePlayerPacket::Rot::getPacketId() {
    return EPacketType::_ServerboundMovePlayerRotPacket;
}

void ServerboundMovePlayerPacket::Rot::read(DataInputStream* input) {
    mYRot = input->readFloat();
    mXRot = input->readFloat();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::Rot::write(DataOutputStream* output) {
    output->writeFloat(mYRot);
    output->writeFloat(mXRot);
    ServerboundMovePlayerPacket::write(output);
}

ServerboundMovePlayerPacket::PosRot::PosRot() {
    hasPos = true;
    hasRot = true;
}

int ServerboundMovePlayerPacket::PosRot::getEstimatedSize() {
    return 41;
}

EPacketType ServerboundMovePlayerPacket::PosRot::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPosRotPacket;
}

void ServerboundMovePlayerPacket::PosRot::read(DataInputStream* input) {
    mX = input->readDouble();
    mY = input->readDouble();
    mZ = input->readDouble();
    mYRot = input->readFloat();
    mXRot = input->readFloat();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::PosRot::write(DataOutputStream* output) {
    output->writeDouble(mX);
    output->writeDouble(mY);
    output->writeDouble(mZ);
    output->writeFloat(mYRot);
    output->writeFloat(mXRot);
    ServerboundMovePlayerPacket::write(output);
}
