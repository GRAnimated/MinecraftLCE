#pragma once

#include "types.h"

class PathNavigationListener {
public:
    PathNavigationListener();
    unsigned char size[0x40];
};

ASSERT_SIZEOF(PathNavigationListener, 0x40)
