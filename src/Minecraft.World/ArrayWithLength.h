#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    arrayWithLength() : length(0) {}
    arrayWithLength(std::vector<T> initialData, int length);
    arrayWithLength(int size, bool a2);

    //~arrayWithLength() { delete[] data; }

    T& get(int index) { return data[index]; }

    explicit operator bool() const { return !data.empty(); }

private:
    std::vector<T> data;
    unsigned int length;
};

template <typename T>
class array2DWithLength {
public:
    array2DWithLength() : lengthX(0), lengthY(0) {}
    array2DWithLength(unsigned int lenX, unsigned int lenY);

    T& get(int index) { return data[index]; }

    explicit operator bool() const { return !data.empty(); }

private:
    std::vector<T> data;
    unsigned int lengthX;
    unsigned int lengthY;
};
