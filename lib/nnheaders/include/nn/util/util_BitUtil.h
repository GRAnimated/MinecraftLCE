#pragma once

#include <nn/util/detail/util_TypeTraits.h>

namespace nn::util {

template <typename T>
T align_up(T x, size_t align) {
    typedef typename detail::MakeUnsigned<T>::Type UIntType;
    UIntType mask = align - 1;
    return (x + mask) & ~mask;
}

}  // namespace nn::util