#pragma once

#include <nn/util/util_BitUtil.h>
#include "nn/types.h"

namespace nn::util {

class BytePtr {
public:
    explicit BytePtr(void* ptr) : m_Ptr(ptr) {}
    BytePtr(void* ptr, ptrdiff_t offset) : BytePtr(ptr) { Advance(offset); }

    void Reset(void* ptr) { m_Ptr = ptr; }

    void* Get() const { return m_Ptr; }

    template <typename T>
    T* Get() const {
        return static_cast<T*>(Get());
    }

    BytePtr& Advance(ptrdiff_t offset) {
        m_Ptr = Get<char>() + offset;
        return *this;
    }

    ptrdiff_t Distance(const void* other) const {
        return static_cast<const char*>(other) - Get<char>();
    }

    // TODO
    bool IsAligned(size_t alignment) const;

    BytePtr& AlignUp(size_t alignment) {
        uintptr_t& ptr = reinterpret_cast<uintptr_t&>(m_Ptr);
        ptr = align_up(ptr, alignment);
        return *this;
    }

    BytePtr& AlignDown(size_t alignment);

    BytePtr& operator+=(ptrdiff_t offset) { return Advance(offset); }
    BytePtr& operator-=(ptrdiff_t offset) { return Advance(-offset); }

    BytePtr operator+(ptrdiff_t offset) const { return BytePtr(*this) += offset; }
    BytePtr operator-(ptrdiff_t offset) const { return BytePtr(*this) -= offset; }

    BytePtr operator++(int) { return BytePtr(*this) + 1; }
    BytePtr& operator++() { return Advance(1); }

    BytePtr operator--(int) { return BytePtr(*this) - 1; }
    BytePtr& operator--() { return Advance(-1); }

private:
    void* m_Ptr;
};

class ConstBytePtr {
public:
    explicit ConstBytePtr(const void* ptr) : m_Ptr(ptr) {}
    ConstBytePtr(const BytePtr&);
    ConstBytePtr(const void* ptr, ptrdiff_t offset) : ConstBytePtr(ptr) { Advance(offset); }

    void Reset(const void*);

    const void* Get() const { return m_Ptr; }

    template <typename T>
    const T* Get() const {
        return static_cast<const T*>(Get());
    }

    ConstBytePtr& Advance(ptrdiff_t offset) {
        m_Ptr = Get<char>() + offset;
        return *this;
    }

    ptrdiff_t Distance(const void* ptr) const {
        return static_cast<const char*>(ptr) - Get<char>();
    }

    bool IsAligned(size_t) const;
    ConstBytePtr& AlignUp(size_t);
    ConstBytePtr& AlignDown(size_t);
    ConstBytePtr& operator+=(ptrdiff_t);
    ConstBytePtr& operator-=(ptrdiff_t);
    ConstBytePtr operator+(ptrdiff_t) const;
    ConstBytePtr operator-(ptrdiff_t) const;
    ConstBytePtr operator++(int);
    ConstBytePtr& operator++();
    ConstBytePtr operator--(int);
    ConstBytePtr& operator--();

private:
    const void* m_Ptr;
};

}  // namespace nn::util
