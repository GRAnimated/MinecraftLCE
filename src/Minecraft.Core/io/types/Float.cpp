//
// Created by DexrnZacAttack on 4/20/2025 (ZPC-I1)
//

#include "Float.h"

inline int Float::floatToIntBits(float value) {
    return *reinterpret_cast<int*>(&value);
}