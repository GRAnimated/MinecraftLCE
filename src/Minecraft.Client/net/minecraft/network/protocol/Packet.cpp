#include "net/minecraft/network/protocol/Packet.h"

#include "net/minecraft/core/System.h"

#include <sstream>

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

// amazing
bool Packet::isAync() {
    return false;
}

bool Packet::tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>* duplicatePacket) {
    return false;
}

std::wstring Packet::readUtf(DataInputStream* in, int maxLength) {
    short length = in->readShort();

    if (length > maxLength) {
        std::wstringstream warning;
        warning << L"Received string length longer than maximum allowed (" << length << L" > " << maxLength
                << L")";
    }

    std::wstring str = L"";
    for (int i = 0; i < length; ++i) {
        str.push_back(in->readChar());
    }

    return str;
}
