#pragma once

#include <nn/util/util_BytePtr.h>
#include <nn/util/util_StringView.h>
#include "nn/types.h"

namespace nn::util {

// todo: is this here?
constexpr uint32_t MakeSignature(u8 a, u8 b, u8 c, u8 d) {
    return a | (b << 8) | (c << 16) | (d << 24);
}

struct BinFileSignature {
    bool IsValid(const char*) const;
    bool IsValid(int64_t) const;
    void Set(const char*);
    const char* Get() const;
    void SetPacked(int64_t);
    int64_t GetPacked() const;

    union {
        char _str[8];
        int64_t _packed;
    };
};

struct BinBlockSignature {
    // TODO: implement these inline functions
    bool IsValid(const char* signature) const;
    bool IsValid(int32_t signature) const;
    void Set(const char* signature);
    const char* Get() const;
    void SetPacked(int32_t signature);
    int32_t GetPacked() const;

    union {
        char _str[4];
        int32_t _packed;
    };
};

struct BinVersion {
    uint8_t micro;
    uint8_t minor;
    uint16_t major;

    bool IsValid(int, int, int) const;
    void SetPacked(uint32_t);
    uint32_t GetPacked() const;
};

template <typename T>
struct BinTPtr {
    typedef T* pointer;
    typedef const T* const_pointer;  // detail::AddConst
    typedef int64_t difference_type;

    void Clear() { _offset = 0; }

    void Set(pointer ptr) { _ptr = ptr; }
    pointer Get() { return _ptr; }
    const_pointer Get() const { return _ptr; }

    void SetOffset(void* base, void* ptr) { SetOffset(ptr ? BytePtr(base).Distance(ptr) : 0); }
    void SetOffset(difference_type offset) { _offset = offset; }
    difference_type GetOffset() const { return _offset; }

    pointer ToPtr(void* base) const {
        const auto offset = _offset;
        if (offset == 0)
            return nullptr;
        return BytePtr(base, offset).Get<T>();
    }

    void Relocate(void* base) { Set(ToPtr(base)); }
    void Unrelocate(void* base) { SetOffset(base, Get()); }

    union {
        difference_type _offset;
        pointer _ptr;
    };
};

using BinPtr = BinTPtr<void>;

template <typename CharT>
struct BinTString {
    using StringViewType = basic_string_view<CharT>;

    // Make it impossible to accidentally construct a (partial, broken) copy.
    BinTString(const BinTString&) = delete;
    auto operator=(const BinTString&) = delete;

    int GetLength() const { return static_cast<int>(_length); }

    const CharT* GetData() const { return _data; }

    StringViewType Get() const { return {_data, _length}; }

    // NOLINTNEXTLINE(google-explicit-constructor)
    operator StringViewType() const { return Get(); }

    // TODO
    static size_t CalculateSize(int);
    void Initialize(const StringViewType& value);
    BinTString* GetNext();
    const BinTString* GetNext() const;

    u16 _length;
    CharT _data[sizeof(u16) / sizeof(CharT)];
};

using BinString = BinTString<char>;
using BinPtrToString = BinTPtr<BinString>;

}  // namespace nn::util