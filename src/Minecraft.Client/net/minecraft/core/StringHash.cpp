#include "net/minecraft/core/System.h"
#include <cstdint>

// This is the original position-dependent LCE hash, including 32-bit wraparound.
size_t javaStringHashCode(const std::wstring& value) {
    std::uint32_t length = static_cast<std::uint32_t>(value.size());
    std::uint64_t last = length - 1;
    std::uint64_t index = 0;
    std::uint32_t remaining = last;
    std::uint32_t result = 0;
    if (length != 0)
        do {
            std::uint32_t character = static_cast<std::uint32_t>(value[index]);
            character = index >= last ? character : (character * 31u) ^ remaining;
            result += character;
            --remaining;
            ++index;
        } while (index != length);
    return result;
}
