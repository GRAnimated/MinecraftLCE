#include "Packet.h"
#include "Minecraft.System/System.h"

Packet::Packet() {
    mCreatedTime = System::processTimeInMilliSecs();
    field_10 = 0;
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

bool Packet::tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>* packet) {
    return false;
}