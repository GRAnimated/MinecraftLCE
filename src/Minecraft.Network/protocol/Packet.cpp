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

std::wstring Packet::readUtf(DataInputStream *in, int length)
{
    short rLength = in->readShort();
    // this won't match until we can fix this stupid error: use of undeclared identifier 'strtoll_l'
    // if (rLength > length) {
    //     std::wcout << L"Received string length longer than maximum allowed ("
    //                 << rLength << L" > " << length << L")" << std::endl;
    // }

    std::wstring str;
    if (length >= 1) {
        while (length) {
            str.push_back(in->readChar());
            length--;
        }
    }
    
    return str;
}
