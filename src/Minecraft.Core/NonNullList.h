#pragma once

#include "Minecraft.World/ArrayWithLength.h"
template <typename T>
class NonNullList : arrayWithLength<T> {
public:
    static NonNullList<T> withSize(int, const T&);

    T baseNotNull;  // idk if this should be not_null_ptr by default or specified in template
};