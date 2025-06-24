#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    T* data;
    unsigned int length;

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

    T& operator[](unsigned int i) { return data[i]; }

    void resize(unsigned int newSize) {
        if (length == newSize) {
            return;
        }
        T* dataBuffer = createDataBuffer(newSize);
        if (data) {
            int len;
            if (length >= newSize)
                len = newSize;
            else
                len = length;
            copy(dataBuffer, data, len);

            delete[] data;
        }

        data = dataBuffer;
        length = newSize;
    }

    // NON_MATCHING
    static void copy(T* dest, T* src, unsigned int size) {
        if (size) {
            unsigned int i = 0;
            for (; (size & 3) != i; ++i) {
                dest[i] = src[i];
            }
            if (size - 1 >= 3) {
                unsigned int remaining = size - i;
                unsigned int offset = i + 3;
                T* destPtr = dest + offset;
                T* srcPtr = src + offset;
                do {
                    *(destPtr - 3) = *(srcPtr - 3);
                    *(destPtr - 2) = *(srcPtr - 2);
                    *(destPtr - 1) = *(srcPtr - 1);
                    *destPtr = *srcPtr;
                    srcPtr += 4;
                    remaining -= 4;
                    destPtr += 4;
                } while (remaining);
            }
        }
    }

    // maybe this should be a constructor?
    static arrayWithLength<T> createFromOther(arrayWithLength<T> other) {
        arrayWithLength<unsigned char> out(other.length, true);
        out.copy(out.data, other.data, other.length);
        return out;
    }

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