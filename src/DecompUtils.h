#pragma once

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
