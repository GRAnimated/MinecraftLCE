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

// if a function is defined in the header but never used, it's not placed into the final binary
// this define is just an easy way to compile in the future with these missing until they're implemented
#ifdef UNUSED_DELETE
#define DELETE_EXTERNAL = delete  // so we can define external methods found within Wii U Edition
#define DELETE_UNUSED = delete
#else
#define DELETE_EXTERNAL
#define DELETE_UNUSED
#endif

// for types that don't exist in the original executable, and are simply just helpers for decomp code
// cleanliness
#define DECOMP_HELPER

template <typename T>
class not_null_ptr : public std::shared_ptr<T> {
public:
    not_null_ptr() = default;
    not_null_ptr(T* ptr);
    not_null_ptr(const T& other);
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef uint8_t byte;

class Entity;
typedef std::shared_ptr<Entity> SharedEntity;
