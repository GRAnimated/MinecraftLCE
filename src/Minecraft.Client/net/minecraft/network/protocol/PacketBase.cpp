#include "net/minecraft/core/System.h"
#include "net/minecraft/network/protocol/Packet.h"

// Keep the base vtable available without pulling the registration table and
// every concrete packet factory into executables using a few packet types.
Packet::Packet() {
    m_createdTime = System::processTimeInMilliSecs();
    m_shouldDelay = false;
}

Packet::~Packet() = default;

void Packet::handle(PacketListener* listener) {}

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
