#pragma once

#include <nn/util.h>

#include <iterator>

namespace nn::util {
class BitArray {
    NN_NO_COPY(BitArray);

public:
    class iterator;
    class const_iterator;

    typedef bool value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef const bool const_reference;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef int size_type;
    typedef int difference_type;

    class reference {
        BitArray* m_pParent;
        size_type m_Pos;

    public:
        reference& flip();
        operator bool() const;
        reference& operator=(bool);
        reference& operator=(const reference&);
        bool operator~() const;

    private:
        reference(BitArray*, size_type);
    };

    class iterator {
        typedef difference_type difference_type;
        typedef reference reference;
        typedef pointer pointer;

        BitArray* m_pParent;
        difference_type m_Pos;

    public:
        operator const_iterator() const;
        iterator& operator++();
        iterator operator++(difference_type);
        iterator& operator--();
        iterator operator--(difference_type);
        iterator& operator+=(difference_type);
        iterator operator+(difference_type) const;
        iterator& operator-=(difference_type);
        iterator operator-(difference_type) const;
        difference_type operator-(const iterator&) const;
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool operator<(const iterator&) const;
        bool operator>(const iterator&) const;
        bool operator<=(const iterator&) const;
        bool operator>=(const iterator&) const;
        reference operator*() const;
        reference operator[](difference_type) const;

    private:
        iterator(BitArray*, difference_type);
    };

    class const_iterator {
        typedef difference_type difference_type;
        typedef const_reference reference;
        typedef const_pointer pointer;

        const BitArray* m_pParent;
        difference_type m_Pos;

    public:
        const_iterator& operator++();
        const_iterator operator++(difference_type);
        const_iterator& operator--();
        const_iterator operator--(difference_type);
        const_iterator& operator+=(difference_type);
        const_iterator operator+(difference_type) const;
        const_iterator& operator-=(difference_type);
        const_iterator operator-(difference_type) const;
        difference_type operator-(const const_iterator&) const;
        reference operator==(const const_iterator&) const;
        reference operator!=(const const_iterator&) const;
        reference operator<(const const_iterator&) const;
        reference operator>(const const_iterator&) const;
        reference operator<=(const const_iterator&) const;
        reference operator>=(const const_iterator&) const;
        reference operator*() const;
        reference operator[](difference_type) const;

    private:
        const_iterator(const BitArray*, difference_type);
    };

    BitArray();
    BitArray(void* workMemory, [[maybe_unused]] size_t workMemorySize, size_type length)
        : m_pBuf(static_cast<RawType*>(workMemory)), m_Len(length) {}

    void* ResetWorkMemory();
    void* ResetWorkMemory(void*, size_t, size_type);
    size_type size() const;
    size_type count() const;
    bool all() const;
    bool none() const;
    bool any() const;

    bool test(size_type pos) const { return Block(pos) & MakeBlockMask(pos); }

    BitArray& flip();
    BitArray& flip(size_type);
    BitArray& set();

    BitArray& set(size_type pos) {
        Block(pos) |= MakeBlockMask(pos);
        return *this;
    }

    BitArray& set(size_type pos, bool value) {
        if (value) {
            set(pos);
        } else {
            reset(pos);
        }

        return *this;
    }

    BitArray& reset();

    BitArray& reset(size_type pos) {
        Block(pos) &= ~MakeBlockMask(pos);
        return *this;
    }

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    bool operator==(const BitArray&) const;
    bool operator!=(const BitArray&) const;
    bool operator[](size_type) const;
    reference operator[](size_type);
    static void And(BitArray*, const BitArray&, const BitArray&);
    static void Or(BitArray*, const BitArray&, const BitArray&);
    static void Xor(BitArray*, const BitArray&, const BitArray&);
    static void Not(BitArray*, const BitArray&);
    static void RightShift(BitArray*, const BitArray&, size_type);
    static void LeftShift(BitArray*, const BitArray&, size_type);
    static size_t CalculateWorkMemorySize(size_type);

private:
    typedef uint64_t RawType;

    static const size_type BitsPerBlock = 64;
    static const size_type BlockShift = 6;
    static const RawType BlockBitMask = BitsPerBlock - 1;

    RawType& Block(size_type pos) { return m_pBuf[pos >> BlockShift]; }
    const RawType& Block(size_type pos) const { return m_pBuf[pos >> BlockShift]; }

    static RawType MakeBlockMask(size_type pos) { return RawType(1) << (pos & BlockBitMask); }
    size_type GetBlockCount() const;
    RawType MakeLastBlockBitMask() const;

    RawType* m_pBuf;
    size_type m_Len;
};
}  // namespace nn::util