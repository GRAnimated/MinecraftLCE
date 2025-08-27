#pragma once

#include "types.h"
#include <cstdint>

class PlayerUID {
public:
    PlayerUID(int uid = 0); // seems to be allocated in new array which requires paramless constructor
    PlayerUID(std::wstring uuid);
    PlayerUID(class ACTUuid, bool, bool); // todo: make class
    PlayerUID(class FFLCreateID, unsigned int, bool, bool); // todo: make class

    bool operator==(const PlayerUID& other) const;
    bool operator!=(const PlayerUID& other) const;

    const std::wstring UuidString() const;
    const std::wstring toString() const;

    long gap_0;
    long mMostSigBits;  // grabbed from JDK, doubt those are correct but yeah, pure guess
    long mLeastSigBits;
    char byte18;
};
