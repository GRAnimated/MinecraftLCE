#pragma once

#include <sstream>
#include <string>
#include <vector>

/** Additional formatting overload supplied by the Switch runtime.
 */
namespace std {
inline namespace __1 {
wstring to_wstring(bool);
}
}  // namespace std

std::wstring replaceAll(const std::wstring&, const std::wstring&, const std::wstring&);

std::vector<std::wstring>& split(const std::wstring&, wchar_t, std::vector<std::wstring>&);
std::vector<std::wstring> split(const std::wstring&, wchar_t);

template <typename T>
T _fromString(const std::wstring& text) {
    std::wistringstream stream(text);
    T value;
    stream >> value;
    return value;
}
