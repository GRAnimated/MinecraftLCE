#pragma once

#include "net/minecraft/world/ArrayWithLength.h"

template <typename T>
class NonNullList : arrayWithLength<T> {
public:
    NonNullList() = default;

    /** Copies are views of the same array. The owner must delete the backing data;
     * destroying a view only releases its default value, as in the executable.
     */
    static NonNullList<T> withSize(int size, const T& defaultValue) {
        NonNullList<T> list;
        if (size > 0) {
            list.m_data = new T[size];
            list.m_length = size;
            for (unsigned int i = 0; i < list.m_length; ++i)
                list.m_data[i] = defaultValue;
        }
        list.m_baseNotNull = defaultValue;
        return list;
    }

    unsigned int size() const { return this->m_length; }
    T& operator[](unsigned int index) { return this->m_data[index]; }
    const T& operator[](unsigned int index) const { return this->m_data[index]; }
    void set(unsigned int index, const T& value) { this->m_data[index] = value; }

    void clear() {
        for (unsigned int i = 0; i < size(); ++i)
            set(i, m_baseNotNull);
    }

    void deleteData() {
        delete[] this->m_data;
        this->m_data = nullptr;
        this->m_length = 0;
    }

    T m_baseNotNull;  // idk if this should be not_null_ptr by default or specified in template, so decided it
                      // not to be for a while
};
