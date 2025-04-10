#include "Minecraft.Core/System.h"
#include "Minecraft.Network/protocol/Packet.h"

Packet::Packet() {
    mCreatedTime = System::processTimeInMilliSecs();
    mShouldDelay = false;
}

void Packet::handle(PacketListener* listener) {
    return;
}

int Packet::getEstimatedSize() {
    return 8;
}

bool Packet::canBeInvalidated() {
    return false;
}

bool Packet::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return false;
}

bool Packet::isAync() {
    return false;
}

bool Packet::tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>* duplicatePacket) {
    return false;
}
