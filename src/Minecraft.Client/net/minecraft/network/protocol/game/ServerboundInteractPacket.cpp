#include "net/minecraft/network/protocol/game/ServerboundInteractPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundInteractPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundInteractPacket());
}

ServerboundInteractPacket::ServerboundInteractPacket() {
    m_target = 0;
    m_action = eAction::Attack;
    m_hand = InteractionHand::MAIN_HAND;
    m_location = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target) {
    m_target = target->getId();
    m_action = eAction::Attack;
    m_hand = InteractionHand::MAIN_HAND;
    m_location = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target,
                                                     InteractionHand::EInteractionHand hand) {
    m_target = target->getId();
    m_action = eAction::Interact;
    m_hand = hand;
    m_location = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target,
                                                     InteractionHand::EInteractionHand hand, Vec3* location) {
    m_target = target->getId();
    m_action = eAction::InteractAt;
    m_hand = hand;
    m_location = Vec3::newPermanent(location->m_x, location->m_y, location->m_z);
}

int ServerboundInteractPacket::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundInteractPacket::getPacketId() {
    return EPacketType::_ServerboundInteractPacket;
}

void ServerboundInteractPacket::read(DataInputStream* input) {
    m_target = input->readVarInt();
    m_action = static_cast<eAction>(input->readInt());
    if (m_action == eAction::InteractAt) {
        float x = input->readFloat();
        float y = input->readFloat();
        float z = input->readFloat();
        m_location = Vec3::newPermanent(x, y, z);
    }
    if (m_action == eAction::Interact || m_action == eAction::InteractAt) {
        m_hand = static_cast<InteractionHand::EInteractionHand>(input->readByte());
    }
}

void ServerboundInteractPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_target);
    output->writeInt(static_cast<int>(m_action));
    if (m_action == eAction::InteractAt) {
        output->writeFloat(m_location->m_x);
        output->writeFloat(m_location->m_y);
        output->writeFloat(m_location->m_z);
    }
    if (m_action == eAction::Interact || m_action == eAction::InteractAt) {
        output->writeByte(static_cast<unsigned char>(m_hand));
    }
}

void ServerboundInteractPacket::handle(PacketListener* listener) {
    listener->handleInteract(shared_from_this());
}

std::shared_ptr<Entity> ServerboundInteractPacket::getTarget(Level* level) {
    return level->getEntity(m_target);
}

ServerboundInteractPacket::eAction ServerboundInteractPacket::getAction() {
    return m_action;
}

InteractionHand::EInteractionHand ServerboundInteractPacket::getHand() {
    return m_hand;
}

Vec3* ServerboundInteractPacket::getLocation() {
    return Vec3::newTemp(m_location);
}
