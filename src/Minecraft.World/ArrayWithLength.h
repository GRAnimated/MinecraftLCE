#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    arrayWithLength() {}
    //~arrayWithLength() { delete data; }
    arrayWithLength(std::vector<T> initialData, int length);
    arrayWithLength(T* initialData, int length);
    arrayWithLength(int size, bool a2);

    T& get(unsigned int i) { return data[i]; }

    T& operator[](unsigned int i) { return get(i); }

    // explicit operator bool() const { return !data->empty(); }

    T* data = nullptr;
    unsigned int length = 0;
};

template <typename T>
class array2DWithLength {
public:
    array2DWithLength() : lengthX(0), lengthY(0) {}
    array2DWithLength(unsigned int lenX, unsigned int lenY);

    T& get(unsigned int index) { return (*data)[index]; }

    explicit operator bool() const { return !data->empty(); }

    std::vector<T>* data = nullptr;
    unsigned int lengthX = 0;
    unsigned int lengthY = 0;
};