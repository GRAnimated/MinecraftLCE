#pragma once

#include "net/minecraft/network/syncher/EntityDataSerializerEnum.h"

class EntityDataSerializerEnum {
public:
    enum EEntityDataSerializer {
        BYTE = 0,
        INT = 1,
        FLOAT = 2,
        STRING = 3,
        ITEM_INSTANCE = 4,
        BLOCK_STATE = 5,
        BOOLEAN = 6,
        ROTATIONS = 7,
        BLOCK_POS = 8,
        OPTIONAL_BLOCK_POS = 9,
        DIRECTION = 10,
        COMPOUND_TAG = 11
    };
};
