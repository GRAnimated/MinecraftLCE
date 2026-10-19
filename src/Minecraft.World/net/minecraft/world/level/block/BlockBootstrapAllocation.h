#pragma once

#include <cstddef>
#include <new>

/** Custom allocation tag for partial block layouts; preserves allocation before argument evaluation. */
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
