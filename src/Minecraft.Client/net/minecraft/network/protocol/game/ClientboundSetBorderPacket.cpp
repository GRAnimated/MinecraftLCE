#include "net/minecraft/network/protocol/game/ClientboundSetBorderPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetBorderPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetBorderPacket());
}

ClientboundSetBorderPacket::ClientboundSetBorderPacket() {}

EPacketType ClientboundSetBorderPacket::getPacketId() {
    return EPacketType::_ClientboundSetBorderPacket;
}

void ClientboundSetBorderPacket::read(DataInputStream* input) {
    m_updateType = static_cast<Type>(input->readInt());

    switch (m_updateType) {
    case Type::SET_SIZE:
        m_size = input->readDouble();
        break;
    case Type::LERP_SIZE:
        m_newSize = input->readDouble();
        m_size = input->readDouble();
        m_lerpTime = input->readVarLong();
        break;
    case Type::SET_CENTER:
        m_centerX = input->readDouble();
        m_centerZ = input->readDouble();
        break;
    case Type::SET_ALL:
        m_centerX = input->readDouble();
        m_centerZ = input->readDouble();
        m_newSize = input->readDouble();
        m_size = input->readDouble();
        m_lerpTime = input->readVarLong();
        m_absoluteMaxSize = input->readVarInt();
        m_warningBlocks = input->readVarInt();
        m_warningTime = input->readVarInt();
        break;
    case Type::SET_WARNING_TIME:
        m_warningTime = input->readVarInt();
        break;
    case Type::SET_WARNING_BLOCKS:
        m_warningBlocks = input->readVarInt();
        break;
    }
}

void ClientboundSetBorderPacket::write(DataOutputStream* output) {
    output->writeInt(static_cast<int>(m_updateType));

    switch (m_updateType) {
    case Type::SET_SIZE:
        output->writeDouble(m_size);
        break;
    case Type::LERP_SIZE:
        output->writeDouble(m_newSize);
        output->writeDouble(m_size);
        output->writeVarLong(m_lerpTime);
        break;
    case Type::SET_CENTER:
        output->writeDouble(m_centerX);
        output->writeDouble(m_centerZ);
        break;
    case Type::SET_ALL:
        output->writeDouble(m_centerX);
        output->writeDouble(m_centerZ);
        output->writeDouble(m_newSize);
        output->writeDouble(m_size);
        output->writeVarLong(m_lerpTime);
        output->writeVarInt(m_absoluteMaxSize);
        output->writeVarInt(m_warningBlocks);
        output->writeVarInt(m_warningTime);
        break;
    case Type::SET_WARNING_TIME:
        output->writeVarInt(m_warningTime);
        break;
    case Type::SET_WARNING_BLOCKS:
        output->writeVarInt(m_warningBlocks);
        break;
    }
}

void ClientboundSetBorderPacket::handle(PacketListener* listener) {
    listener->handleSetBorder(shared_from_this());
}

void ClientboundSetBorderPacket::applyChanges(WorldBorder* border) {
    switch (this->m_updateType) {
    case Type::SET_SIZE:
        border->setSize(this->m_size);
        break;
    case Type::LERP_SIZE:
        border->lerpSizeBetween(this->m_newSize, this->m_size, this->m_lerpTime);
        break;
    case Type::SET_CENTER:
        border->setCenter(this->m_centerX, this->m_centerZ);
        break;
    case Type::SET_ALL:
        border->setCenter(this->m_centerX, this->m_centerZ);
        if (this->m_lerpTime < 1) {
            border->setSize(this->m_size);
        } else {
            border->lerpSizeBetween(this->m_newSize, this->m_size, this->m_lerpTime);
        }

        border->setAbsoluteMaxSize(this->m_absoluteMaxSize);
        border->setWarningBlocks(this->m_warningBlocks);
        border->setWarningTime(this->m_warningTime);
        break;
    case Type::SET_WARNING_TIME:
        border->setWarningTime(this->m_warningTime);
        break;
    case Type::SET_WARNING_BLOCKS:
        border->setWarningBlocks(this->m_warningBlocks);
        break;
    }
}
