#pragma once

#include <nn/types.h>
#include <type_traits>

namespace nn::util {

template <class T, size_t Size, size_t Alignment>
struct TypedStorage {
    alignas(Alignment) char storage[Size];
};

}  // namespace nn::util