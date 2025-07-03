#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
template <typename T>
class NonNullList : arrayWithLength<T> {
public:
    static NonNullList<T> withSize(int, const T&);

    T baseNotNull;  // idk if this should be not_null_ptr by default or specified in template, so decided it
                    // not to be for a while
};
