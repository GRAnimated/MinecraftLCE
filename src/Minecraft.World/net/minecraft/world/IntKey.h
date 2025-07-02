#pragma once

#include <cstddef>
#include <functional>

struct IntKeyHash {
    // NON_MATCHING
    std::size_t operator()(int key) const noexcept { return std::hash<int>{}(key); }
};

struct IntKeyHash2 {
    // NON_MATCHING
    std::size_t operator()(int key) const noexcept { return std::hash<int>{}(key); }
};

struct IntKeyEq {
    // NON_MATCHING
    bool operator()(int lhs, int rhs) const noexcept { return lhs == rhs; }
};
