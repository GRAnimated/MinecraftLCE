#pragma once

#include <arm_neon.h>
#include <cmath>

// this can be depracated if musl is fixed

inline __attribute__((__always_inline__)) float decomp_fmax1(float x, float y) {
    __asm__("fmax %s0, %s1, %s2" : "=w"(x) : "w"(x), "w"(y));
    return x;
}

inline __attribute__((__always_inline__)) float decomp_fmax(float x, float y) {
    __asm__("fmaxnm %s0, %s1, %s2" : "=w"(x) : "w"(x), "w"(y));
    return x;
}

inline __attribute__((__always_inline__)) float decomp_fminf(float x, float y) {
    __asm__("fminnm %s0, %s1, %s2" : "=w"(x) : "w"(x), "w"(y));
    return x;
}

/** Custom instruction helpers: AArch64 fmax/fmin propagate NaNs, unlike the C math functions. */
inline __attribute__((__always_inline__)) double decomp_fmax64(double x, double y) {
    __asm__("fmax %d0, %d1, %d2" : "=w"(x) : "w"(x), "w"(y));
    return x;
}

inline __attribute__((__always_inline__)) double decomp_fmin64(double x, double y) {
    __asm__("fmin %d0, %d1, %d2" : "=w"(x) : "w"(x), "w"(y));
    return x;
}
