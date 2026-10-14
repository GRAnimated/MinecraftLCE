#include "StringUtils.h"

std::wstring replaceAll(const std::wstring& input, const std::wstring& from, const std::wstring& to) {
    std::wstring result(input);
    std::size_t pos = 0;
    while ((pos = result.find(from, pos)) != std::wstring::npos) {
        result.replace(pos, from.size(), to);
        ++pos;  // Original advances by one, including when replacement shrinks.
    }
    return result;
}
