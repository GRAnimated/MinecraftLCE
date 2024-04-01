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
