#pragma once

#include <nn/util/MathTypes.h>
#include <nn/util/detail/util_ArithmeticImpl.h>

namespace nn::util {

inline AngleIndex RadianToAngleIndex(float radian) {
    return static_cast<int64_t>(radian * (detail::AngleIndexHalfRound / detail::FloatPi));
}

inline float DegreeToRadian(float degree) {
    return degree * (detail::FloatPi / detail::FloatDegree180);
}

inline float SinTable(AngleIndex angleIndex) {
    uint32_t sampleTableIndex = (angleIndex >> 24) & 0xFF;
    float rest = static_cast<float>(angleIndex & 0xFFFFFF) / 0x1000000;
    const detail::SinCosSample* table = &detail::SinCosSampleTable[sampleTableIndex];
    return table->sinValue + table->sinDelta * rest;
}

inline float CosTable(AngleIndex angleIndex) {
    uint32_t sampleTableIndex = (angleIndex >> 24) & 0xFF;
    const detail::SinCosSample* table = &detail::SinCosSampleTable[sampleTableIndex];
    float rest = static_cast<float>(angleIndex & 0xFFFFFF) / 0x1000000;
    return table->cosValue + table->cosDelta * rest;
}

}  // namespace nn::util