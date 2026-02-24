#include "ServerboundMovePlayerPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundMovePlayerPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundMovePlayerPacket());
}

ServerboundMovePlayerPacket::ServerboundMovePlayerPacket() {
    m_x = 0.0;
    m_y = 0.0;
    m_z = 0.0;
    m_yRot = 0.0;
    m_xRot = 0.0;
    m_hasRot = false;
    m_hasPos = false;
    m_onGround = false;
    m_bool3B = false;
}

int ServerboundMovePlayerPacket::getEstimatedSize() {
    return 1;
}

EPacketType ServerboundMovePlayerPacket::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPacket;
}

void ServerboundMovePlayerPacket::read(DataInputStream* input) {
    int8_t flags = static_cast<int8_t>(input->readByte());
    m_onGround = flags & 1;
    m_bool3B = (flags >> 1) & 1;
}

void ServerboundMovePlayerPacket::write(DataOutputStream* output) {
    uint8_t fOnGround = static_cast<uint8_t>(m_onGround);
    uint8_t fBool3B = static_cast<uint8_t>(m_bool3B) << 1;
    uint8_t flags = fOnGround | fBool3B;
    output->writeByte(flags);
}

void ServerboundMovePlayerPacket::handle(PacketListener* listener) {
    listener->handleMovePlayer(shared_from_this());
}

double ServerboundMovePlayerPacket::getX(double x) {
    return m_hasPos ? m_x : x;
}

double ServerboundMovePlayerPacket::getY(double y) {
    return m_hasPos ? m_y : y;
}

double ServerboundMovePlayerPacket::getZ(double z) {
    return m_hasPos ? m_z : z;
}

float ServerboundMovePlayerPacket::getYRot(float yRot) {
    return m_hasRot ? m_yRot : yRot;
}

float ServerboundMovePlayerPacket::getXRot(float xRot) {
    return m_hasRot ? m_xRot : xRot;
}

bool ServerboundMovePlayerPacket::isOnGround() {
    return m_onGround;
}

ServerboundMovePlayerPacket::Pos::Pos() {
    m_hasPos = true;
}

int ServerboundMovePlayerPacket::Pos::getEstimatedSize() {
    return 33;
}

EPacketType ServerboundMovePlayerPacket::Pos::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPosPacket;
}

void ServerboundMovePlayerPacket::Pos::read(DataInputStream* input) {
    m_x = input->readDouble();
    m_y = input->readDouble();
    m_z = input->readDouble();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::Pos::write(DataOutputStream* output) {
    output->writeDouble(m_x);
    output->writeDouble(m_y);
    output->writeDouble(m_z);
    ServerboundMovePlayerPacket::write(output);
}

ServerboundMovePlayerPacket::Rot::Rot() {
    m_hasRot = true;
}

int ServerboundMovePlayerPacket::Rot::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundMovePlayerPacket::Rot::getPacketId() {
    return EPacketType::_ServerboundMovePlayerRotPacket;
}

void ServerboundMovePlayerPacket::Rot::read(DataInputStream* input) {
    m_yRot = input->readFloat();
    m_xRot = input->readFloat();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::Rot::write(DataOutputStream* output) {
    output->writeFloat(m_yRot);
    output->writeFloat(m_xRot);
    ServerboundMovePlayerPacket::write(output);
}

ServerboundMovePlayerPacket::PosRot::PosRot() {
    m_hasPos = true;
    m_hasRot = true;
}

int ServerboundMovePlayerPacket::PosRot::getEstimatedSize() {
    return 41;
}

EPacketType ServerboundMovePlayerPacket::PosRot::getPacketId() {
    return EPacketType::_ServerboundMovePlayerPosRotPacket;
}

void ServerboundMovePlayerPacket::PosRot::read(DataInputStream* input) {
    m_x = input->readDouble();
    m_y = input->readDouble();
    m_z = input->readDouble();
    m_yRot = input->readFloat();
    m_xRot = input->readFloat();
    ServerboundMovePlayerPacket::read(input);
}

void ServerboundMovePlayerPacket::PosRot::write(DataOutputStream* output) {
    output->writeDouble(m_x);
    output->writeDouble(m_y);
    output->writeDouble(m_z);
    output->writeFloat(m_yRot);
    output->writeFloat(m_xRot);
    ServerboundMovePlayerPacket::write(output);
}
