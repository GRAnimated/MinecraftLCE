#include "Float.h"

inline int Float::floatToIntBits(float value) {
    return *reinterpret_cast<int*>(&value);
}