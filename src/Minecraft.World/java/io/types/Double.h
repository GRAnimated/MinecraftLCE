#pragma once

class Double {
public:
    static long long doubleToLongBits(double value);

    static bool checkNan(double value) { return value != value; }
    static long long convertToLong(double value) { return *reinterpret_cast<long long*>(&value); }
};
