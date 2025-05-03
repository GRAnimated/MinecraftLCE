#pragma once

#include "types.h"
#include <cstdint>
class PlayerUID {
public:
    PlayerUID(int uid);

    char char0;
    char gap1[7];
    void* qword8;
    void* qword10;
    char byte18;
};
