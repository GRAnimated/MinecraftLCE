//
// Created by DexrnZacAttack on 4/20/2025 (ZPC-I1)
//
#pragma once

class Double {
public:
    static long long doubleToLongBits(double value);

    static bool checkNan(double value) { return value != value; }
    static long long convertToLong(double value) { return *reinterpret_cast<long long*>(&value); }
};