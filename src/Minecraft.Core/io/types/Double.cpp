//
// Created by DexrnZacAttack on 4/20/2025 (ZPC-I1)
//

#include "Double.h"

long long Double::doubleToLongBits(double value) {
    checkNan(value); // ????
    return convertToLong(value);
}