#include "java/io/File.h"

#include <cstdlib>
#include <cstring>

#include "fui/fuiFile.h"

File::File() {
    this->m_name = L"";
}

File::File(const std::wstring& name) {
    if (!name.empty()) {
        this->m_name = name;
    } else {
        this->m_name = std::wstring(L"");
    }
}

// NON_MATCHING | score: 1075 (lower is better)
File::File(const File& rhs, const std::wstring& name) {
    this->m_name = rhs.getPath() + L"\\" + name;
}

File::~File() = default;

// NON_MATCHING | score: 805 (lower is better)
File& File::operator=(const File& rhs) {
    this->m_name.clear();
    this->m_name = rhs.m_name;
    return *this;
}

std::wstring File::getPath() const {
    return m_name;
}

// NON_MATCHING | score: 1248 (lower is better)
std::wstring File::getName() const {
    int separator = static_cast<int>(m_name.rfind(L'\\'));
    if (separator == -1)
        separator = static_cast<int>(m_name.rfind(L'/'));
    return std::wstring(m_name, separator + 1, m_name.size());
}

// NON_MATCHING | score: 2980 (lower is better)
std::wstring File::ext() const {
    const std::wstring name = getName();
    const auto dot = name.find(std::wstring(L"."));
    // The executable uses the first dot and includes it in the extension.
    if (dot == std::wstring::npos || dot == 0)
        return std::wstring(L"");
    return std::wstring(name, dot, std::wstring::npos);
}

int DeleteFileA(const char*);

// NON_MATCHING | score: 1020 (lower is better)
bool File::_delete() {
    char buffer[256];
    const bool result = DeleteFileA(wstringtofilename(getPath(), buffer)) != 0;
    if (!result)
        GetLastError();
    return result;
}

bool File::mkdir() const {
    char buffer[256];
    return CreateDirectoryA(wstringtofilename(getPath(), buffer), nullptr) != 0;
}

bool File::exists() const {
    char buffer[256];
    return GetFileAttributesA(wstringtofilename(getPath(), buffer)) != -1;
}

bool isDirectory(const std::wstring& path) {
    const File& file = reinterpret_cast<const File&>(path);
    if (!file.exists())
        return false;
    char buffer[256];
    return (GetFileAttributesA(wstringtofilename(file.getPath(), buffer)) & 0x10) != 0;
}

// name guessed
// NON_MATCHING | score: 800 (lower is better)
bool File::renameTo(File dest) {
    char buffer[256];
    const std::string source(wstringtofilename(getPath(), buffer));
    const char* destination = wstringtofilename(dest.getPath(), buffer);
    const bool result = MoveFileA(source.c_str(), destination) != 0;
    if (!result)
        GetLastError();
    return result;
}

long File::length() {
    char buffer[256];
    auto* handle
        = CreateFileA(wstringtofilename(getPath(), buffer), 0x80000000, 0, nullptr, 3, 0x80, nullptr);
    if (handle == reinterpret_cast<nn::fs::FileHandle*>(-1))
        return 0;
    const int size = GetFileSize(handle, nullptr);
    CloseHandle(handle);
    return size;
}

// NON_MATCHING | score: 515 (lower is better)
const char* wstringtofilename(const std::wstring& name, char (&buffer)[256]) {
    for (unsigned int i = 0; i < name.size(); ++i)
        buffer[i] = static_cast<char>(name[i] == L'/' ? L'\\' : name[i]);
    buffer[name.size()] = 0;
    return buffer;
}

// NON_MATCHING | score: 3213 (lower is better)
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

/** These two legacy Windows adapters really are constant-return stubs in the
 * Switch executable (0x71006081f0 and 0x7100608514). Do not use them on PC.
 */

// name guessed
int DeleteFileA(const char*) {
    return 0;
}

// name guessed
bool WriteFile(nn::fs::FileHandle*, const void*, unsigned int, unsigned int*, _OVERLAPPED*) {
    return true;
}
