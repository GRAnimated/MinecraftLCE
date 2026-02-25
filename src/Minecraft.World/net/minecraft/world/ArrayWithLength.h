#pragma once

#include <vector>

template <typename T>
class arrayWithLength {
public:
    T* m_data;
    unsigned int m_length;

    arrayWithLength() {
        this->m_data = nullptr;
        this->m_length = 0;
    }
    // ~arrayWithLength() { delete data; }
    arrayWithLength(std::vector<T> initialData, int length);
    arrayWithLength(T* initialData, int length) {
        this->m_data = initialData;
        this->m_length = length;
    }
    arrayWithLength(unsigned int size, bool a3) {
        T* temp;
        if (a3)
            temp = createDataBuffer(size);
        else
            temp = (T*)operator new[](sizeof(T) * size);
        this->m_data = temp;
        this->m_length = size;
    }

    T& operator[](unsigned int i) { return m_data[i]; }
    T& get(unsigned int i) { return m_data[i]; }

    void resize(unsigned int newSize) {
        if (m_length == newSize) {
            return;
        }
        T* dataBuffer = createDataBuffer(newSize);
        if (m_data) {
            int len;
            if (m_length >= newSize)
                len = newSize;
            else
                len = m_length;
            copy(dataBuffer, m_data, len);

            delete[] m_data;
        }

        m_data = dataBuffer;
        m_length = newSize;
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
        arrayWithLength<unsigned char> out(other.m_length, true);
        out.copy(out.m_data, other.m_data, other.m_length);
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
    array2DWithLength() : m_lengthX(0), m_lengthY(0) {}
    array2DWithLength(unsigned int lenX, unsigned int lenY);

    T& get(unsigned int index) { return (*m_data)[index]; }

    explicit operator bool() const { return !m_data->empty(); }

    std::vector<T>* m_data = nullptr;
    unsigned int m_lengthX = 0;
    unsigned int m_lengthY = 0;
};
