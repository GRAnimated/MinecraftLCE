#pragma once

#include <string>

namespace nn::util {

// todo: verify implementations of these functions
// most are currently just a copy of clang 4.0.1's string_view
template <typename charT, typename traits = std::char_traits<charT>>
class basic_string_view {
public:
    typedef basic_string_view<charT, traits> self_type;
    typedef const charT* const_pointer;
    typedef const charT& const_reference;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;

    static const size_type npos = static_cast<size_type>(-1);

    basic_string_view() : m_Str(nullptr), m_Len(0) {}
    basic_string_view(const_pointer str, size_type len) : m_Str(str), m_Len(len) {}
    basic_string_view(const_pointer str) : m_Str(str), m_Len(str ? traits::length(str) : 0) {}

    const_pointer begin() const { return m_Str; }
    const_pointer end() const { return m_Str + m_Len; }
    const_pointer cbegin() const { return m_Str; }
    const_pointer cend() const { return m_Str + m_Len; }
    const_reverse_iterator rbegin() const { return end(); }
    const_reverse_iterator rend() const { return begin(); }
    const_reverse_iterator crbegin() const { return cend(); }
    const_reverse_iterator crend() const { return cbegin(); }

    size_type size() const { return m_Len; }
    size_type length() const { return m_Len; }
    const_pointer data() const { return m_Str; }
    bool empty() const { return m_Len == 0; }

    self_type substr(size_type pos = 0, size_type n = npos) const {
        size_type rlen = std::min(n, size() - pos);
        return self_type(data() + pos, rlen);
    }

    const_reference operator[](size_type pos) const { return m_Str[pos]; }
    const_reference at(size_type pos) const { return m_Str[pos]; }
    const_reference front() const { return m_Str[0]; }
    const_reference back() const { return m_Str[m_Len - 1]; }

    void clear() {
        m_Str = nullptr;
        m_Len = 0;
    }

    void remove_prefix(size_type n) {
        m_Str += n;
        m_Len -= n;
    }

    void remove_suffix(size_type n) { m_Len -= n; }

    int compare(const self_type& str) const {
        size_type rlen = std::min(m_Len, str.m_Len);
        int result = traits::compare(m_Str, str.m_Str, rlen);
        if (result != 0) {
            return result;
        } else if (str.size() < size()) {
            return 1;
        } else if (size() < str.size()) {
            return -1;
        }
        return 0;
    }

    int compare(const_pointer str) const { return compare(self_type(str)); }

    // todo: implement these, not sure what's the best way for cross compat
    size_type find(const self_type& str, size_type pos = 0) const;
    size_type find(charT c, size_type pos = 0) const;
    size_type find(const_pointer str, size_type pos = 0) const;
    size_type rfind(const self_type& str, size_type pos = 0) const;
    size_type rfind(charT c, size_type pos = 0) const;
    size_type rfind(const_pointer str, size_type pos = 0) const;
    size_type find_first_of(const self_type& str, size_type pos = 0) const;
    size_type find_first_of(const_pointer str, size_type pos = 0) const;
    size_type find_last_of(const self_type& str, size_type pos = 0) const;
    size_type find_last_of(const_pointer str, size_type pos = 0) const;
    size_type find_first_not_of(const self_type& str, size_type pos = 0) const;
    size_type find_first_not_of(charT c, size_type pos = 0) const;
    size_type find_first_not_of(const_pointer str, size_type pos = 0) const;
    size_type find_last_not_of(const self_type& str, size_type pos = 0) const;
    size_type find_last_not_of(charT c, size_type pos = 0) const;
    size_type find_last_not_of(const_pointer str, size_type pos = 0) const;

    friend bool operator==(const basic_string_view& lhs, const basic_string_view& rhs) {
        return lhs.compare(rhs) == 0;
    }

    friend bool operator!=(const basic_string_view& lhs, const basic_string_view& rhs) {
        return lhs.compare(rhs) != 0;
    }

private:
    const_pointer m_Str;
    size_type m_Len;
};

using string_view = basic_string_view<char>;

}  // namespace nn::util
