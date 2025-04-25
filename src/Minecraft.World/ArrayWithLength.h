#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    arrayWithLength() {
        this->data = nullptr;
        this->length = 0;
    }
    // ~arrayWithLength() { delete data; }
    arrayWithLength(std::vector<T> initialData, int length);
    arrayWithLength(T* initialData, int length) {
        this->data = initialData;
        this->length = length;
    }
    arrayWithLength(unsigned int size, bool a3) {
        T* temp;
        if (a3)
            temp = createDataBuffer(size);
        else
            temp = (T*)operator new[](sizeof(T) * size);
        this->data = temp;
        this->length = size;
    }

    // T& get(unsigned int i) { return data[i]; }//

    T& operator[](unsigned int i) { return data[i]; }

    // explicit operator bool() const { return !data->empty(); }

    T* data;
    unsigned int length;

private:
    static T* createDataBuffer(unsigned int size) {
        T* buffer = (T*)operator new[](sizeof(T) * size);
        for (unsigned int i = 0; i < size; i++) {
            new (buffer + i) T();
        }
        return buffer;
    }
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