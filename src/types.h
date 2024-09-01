#pragma once

#include <memory>
#include "nn/types.h"

#ifdef SAFETY_CHECKS
#define ASSERT_SIZEOF(Class, Size) static_assert(sizeof(Class) == Size, "Size of " #Class " is not " #Size " bytes.");
#else
#define ASSERT_SIZEOF(Class, Size)
#endif

template <typename T>
class not_null_ptr : public std::shared_ptr<T> {};

typedef unsigned char uchar;
typedef unsigned int uint;

class Entity;
typedef std::shared_ptr<Entity> SharedEntity;