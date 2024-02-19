#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    arrayWithLength(unsigned int size, bool isFixedSize) : size(size), isFixedSize(isFixedSize) {}
    void resize(unsigned int length);

private:
    std::vector<uint8_t> array;
    unsigned int size;
    bool isFixedSize;
};