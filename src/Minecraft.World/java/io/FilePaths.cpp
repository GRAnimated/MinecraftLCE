#include "java/io/File.h"
#include <cstdlib>
#include <cstring>

const char* wstringtofilename(const std::wstring& name, char (&buffer)[256]) {
    for (unsigned int i = 0; i < name.size(); ++i)
        buffer[i] = static_cast<char>(name[i] == L'/' ? L'\\' : name[i]);
    buffer[name.size()] = 0;
    return buffer;
}

std::wstring filenametowstring(const char* name) {
    const std::string encoded(name);
    const auto length = encoded.size() + 1;
    wchar_t* buffer = new wchar_t[length];
    std::mbstowcs(buffer, encoded.c_str(), length);
    const std::wstring decoded(buffer);
    delete[] buffer;
    return decoded;
}

std::wstring char16towstring(wchar_t* name) {
    // FileEntry stores 16-bit characters even where wchar_t is 32 bits.
    const unsigned short* units = reinterpret_cast<const unsigned short*>(name);
    std::wstring decoded;
    while (*units)
        decoded.push_back(*units++);
    return decoded;
}
