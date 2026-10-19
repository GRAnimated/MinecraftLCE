#pragma once

#include "types.h"
#include <cstdint>
#include <string>

class PlayerUID {
public:
    PlayerUID(int uid = 0);  // seems to be allocated in new array which requires paramless constructor
    PlayerUID(std::wstring uuid);
    PlayerUID(class ACTUuid, bool, bool);                    // todo: make class
    PlayerUID(class FFLCreateID, unsigned int, bool, bool);  // todo: make class

    bool operator==(const PlayerUID& other) const;
    bool operator!=(const PlayerUID& other) const;

    const std::wstring UuidString() const;
    const std::wstring toString() const;

    long m_gap0;
    long m_mostSigBits;   // name guessed: UUID high bits
    long m_leastSigBits;  // name guessed: UUID low bits
    char m_byte18;
};
