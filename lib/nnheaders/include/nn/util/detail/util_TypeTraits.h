#pragma once

#include <nn/types.h>

namespace nn::util::detail {

template <int N>
struct SizedInt;

template <>
struct SizedInt<8> {
    typedef uint64_t Unsigned;
};

template <class T>
struct ChangeSign {
    typedef typename SizedInt<sizeof(T)>::Unsigned Unsigned;
};

template <class T>
struct MakeUnsigned {
    typedef typename ChangeSign<T>::Unsigned Type;
};

}  // namespace nn::util::detail