#pragma once

#include <cstddef>
#include <new>

// Several block declarations still expose only their reconstructed prefix.
// Keep the original initializer's allocation size without inventing fields or
// changing those partial class layouts. Placement-new retains allocation before
// constructor argument evaluation, as in the original new expression.
template <std::size_t OriginalSize>
struct BlockBootstrapAllocation {};

template <std::size_t OriginalSize>
inline __attribute__((always_inline)) void* operator new(std::size_t declaredSize,
                                                         BlockBootstrapAllocation<OriginalSize>) {
    return ::operator new(OriginalSize);
}

template <std::size_t OriginalSize>
inline void operator delete(void* pointer, BlockBootstrapAllocation<OriginalSize>) noexcept {
    ::operator delete(pointer);
}
