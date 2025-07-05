#include "java/io/types/Double.h"

long long Double::doubleToLongBits(double value) {
    checkNan(value);  // ????
    return convertToLong(value);
}
