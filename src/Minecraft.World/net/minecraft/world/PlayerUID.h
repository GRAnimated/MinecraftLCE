#pragma once

#include "java/io/JavaLong.h"
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

    JavaLong m_gap0;
    JavaLong m_mostSigBits;  // grabbed from JDK, doubt those are correct but yeah, pure guess
    JavaLong m_leastSigBits;
    char m_byte18;
};
