#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    arrayWithLength() {}
    arrayWithLength(std::vector<T> initialData, int length);
    arrayWithLength(int size, bool a2);

    // NON_MATCHING
    T& get(unsigned int index) { return (*data)[index]; }

    explicit operator bool() const { return !data->empty(); }

    std::vector<T>* data = nullptr;
    unsigned int length = 0;
};

template <typename T>
class array2DWithLength : public std::vector<T> {
public:
    array2DWithLength() : lengthX(0), lengthY(0) {}
    array2DWithLength(unsigned int lenX, unsigned int lenY);

    T& get(int index) { return (*data)[index]; }

    explicit operator bool() const { return !data->empty(); }

private:
    std::vector<T>* data = nullptr;
    unsigned int lengthX;
    unsigned int lengthY;
};
