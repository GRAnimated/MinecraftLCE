#include "ServerboundInteractPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundInteractPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundInteractPacket());
}

ServerboundInteractPacket::ServerboundInteractPacket() {
    mTarget = 0;
    mAction = eAction::Attack;
    mHand = InteractionHand::MAIN_HAND;
    mLocation = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target) {
    mTarget = target->getId();
    mAction = eAction::Attack;
    mHand = InteractionHand::MAIN_HAND;
    mLocation = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target,
                                                     InteractionHand::EInteractionHand hand) {
    mTarget = target->getId();
    mAction = eAction::Interact;
    mHand = hand;
    mLocation = 0;
}

ServerboundInteractPacket::ServerboundInteractPacket(std::shared_ptr<Entity> target,
                                                     InteractionHand::EInteractionHand hand, Vec3* location) {
    mTarget = target->getId();
    mAction = eAction::InteractAt;
    mHand = hand;
    mLocation = Vec3::newPermanent(location->x, location->y, location->z);
}

int ServerboundInteractPacket::getEstimatedSize() {
    return 9;
}

EPacketType ServerboundInteractPacket::getPacketId() {
    return EPacketType::_ServerboundInteractPacket;
}

void ServerboundInteractPacket::read(DataInputStream* input) {
    mTarget = input->readVarInt();
    mAction = static_cast<eAction>(input->readInt());
    if (mAction == eAction::InteractAt) {
        float x = input->readFloat();
        float y = input->readFloat();
        float z = input->readFloat();
        mLocation = Vec3::newPermanent(x, y, z);
    }
    if (mAction == eAction::Interact || mAction == eAction::InteractAt) {
        mHand = static_cast<InteractionHand::EInteractionHand>(input->readByte());
    }
}

void ServerboundInteractPacket::write(DataOutputStream* output) {
    output->writeVarInt(mTarget);
    output->writeInt(static_cast<int>(mAction));
    if (mAction == eAction::InteractAt) {
        output->writeFloat(mLocation->x);
        output->writeFloat(mLocation->y);
        output->writeFloat(mLocation->z);
    }
    if (mAction == eAction::Interact || mAction == eAction::InteractAt) {
        output->writeByte(static_cast<unsigned char>(mHand));
    }
}

void ServerboundInteractPacket::handle(PacketListener* listener) {
    listener->handleInteract(shared_from_this());
}

std::shared_ptr<Entity> ServerboundInteractPacket::getTarget(Level* level) {
    return level->getEntity(mTarget);
}

ServerboundInteractPacket::eAction ServerboundInteractPacket::getAction() {
    return mAction;
}

InteractionHand::EInteractionHand ServerboundInteractPacket::getHand() {
    return mHand;
}

Vec3* ServerboundInteractPacket::getLocation() {
    return Vec3::newTemp(mLocation);
}
