#pragma once

#include <nn/types.h>

namespace nn::util {

typedef uint32_t AngleIndex;

struct Float2 {
    union {
        float v[2];
        struct {
            float x;
            float y;
        };
    };
};

struct Float3 {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
    };
};

struct Float4 {
    union {
        float v[4];
        struct {
            float x;
            float y;
            float z;
            float w;
        };
    };
};

struct FloatColumnMajor4x3 {
    float m[3][4];
};

struct Unorm8x4 {
    union {
        uint8_t v[4];
    };
};

typedef Unorm8x4 Color4u8Type;

}  // namespace nn::util
