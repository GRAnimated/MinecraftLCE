#pragma once

#include <nn/util/MathTypes.h>

namespace nn::util::detail {
// todo: figure out where to put these
extern float SinCoefficients[5];
extern float CosCoefficients[5];
extern float AtanCoefficients[8];

extern AngleIndex AngleIndexHalfRound;
extern float FloatPiDivided2;
extern float Float1Divided2Pi;
extern float FloatPi;
extern float Float2Pi;
extern float FloatDegree180;
extern float FloatQuaternionEpsilon;
extern float FloatUlp;

struct SinCosSample {
    float cosValue;
    float sinValue;
    float cosDelta;
    float sinDelta;
};

extern SinCosSample SinCosSampleTable[4];

/* todo: implement for shape functions
inline float ModPi(float x) {
    float factor;
    float roundedQuotient;
}
*/

};  // namespace nn::util::detail