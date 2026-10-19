#include "StringUtils.h"

// name guessed
std::wstring replaceAll(const std::wstring& input, const std::wstring& from, const std::wstring& to) {
    std::wstring result(input);
    std::size_t pos = 0;
    while ((pos = result.find(from, pos)) != std::wstring::npos) {
        result.replace(pos, from.size(), to);
        ++pos;  // Original advances by one, including when replacement shrinks.
    }
    return result;
}

// name guessed
std::vector<std::wstring>& split(const std::wstring& text, wchar_t delimiter,
                                 std::vector<std::wstring>& output) {
    std::wstringstream stream(text);
    std::wstring token;
    while (std::getline(stream, token, delimiter))
        output.push_back(token);
    return output;
}

// name guessed
std::vector<std::wstring> split(const std::wstring& text, wchar_t delimiter) {
    std::vector<std::wstring> output;
    return split(text, delimiter, output);
}
