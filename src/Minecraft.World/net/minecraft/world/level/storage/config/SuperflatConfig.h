#pragma once

#include "com/mojang/nbt/ByteArrayTag.h"

class SuperflatConfig {
public:
    ByteArrayTag* toTag();
};
