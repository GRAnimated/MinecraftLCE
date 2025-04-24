#pragma once

#include "nn/types.h"
#include <cstdint>
#include <memory>

#ifdef SAFETY_CHECKS
#define ASSERT_SIZEOF(Class, Size)                                                                           \
    static_assert(sizeof(Class) == Size, "Size of " #Class " is not " #Size " bytes.");
#else
#define ASSERT_SIZEOF(Class, Size)
#endif

template <typename T>
class not_null_ptr : public std::shared_ptr<T> {
public:
    not_null_ptr() = default;
    not_null_ptr(T* ptr);
    not_null_ptr(T const& other);
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef uint8_t byte;

class Entity;
typedef std::shared_ptr<Entity> SharedEntity;
