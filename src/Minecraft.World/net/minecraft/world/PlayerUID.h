#pragma once

#include "types.h"
#include <cstdint>
class PlayerUID {
public:
    PlayerUID(int uid);

    char char0;
    char gap1[7];
    long mMostSigBits;  // grabbed from JDK, doubt those are correct but yeah, pure guess
    long mLeastSigBits;
    char byte18;
};
