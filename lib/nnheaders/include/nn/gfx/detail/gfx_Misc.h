#pragma once

#include <nn/types.h>

namespace nn::gfx::detail {

template <class TType, class TValue = u64>
union Ptr {
    typedef TValue ValueType;
    typedef TType* PtrType;
    typedef Ptr<TType, TValue> SelfType;

    PtrType ptr;
    // doesn't seem to exist in SMO
    // ValueType value;

    PtrType operator->() const { return ptr; }

    PtrType* operator&() { return &ptr; }

    operator PtrType() const { return ptr; }

    template <class T>
    operator T() const {
        return static_cast<T>(ptr);
    }

    operator bool() const { return ptr != nullptr; }

    SelfType& operator=(PtrType p) {
        ptr = p;
        return *this;
    }
};

}  // namespace nn::gfx::detail