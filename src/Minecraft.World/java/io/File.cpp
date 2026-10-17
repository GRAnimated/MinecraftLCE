#include "java/io/File.h"

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

// NON_MATCHING | Score: 1075 (lower is better)
// Some std::wstring shenanigans
File::File(const File& rhs, const std::wstring& name) {
    this->m_name = rhs.getPath() + L"\\" + name;
}

File::~File() = default;

// NON_MATCHING | score: 805 (lower is better)
// Seems like I'm missing some kind of call
// Also, does it clear RHS' string?
File& File::operator=(const File& rhs) {
    this->m_name.clear();
    this->m_name = rhs.m_name;
    return *this;
}

std::wstring File::getPath() const {
    return m_name;
}

std::wstring File::getName() const {
    int separator = static_cast<int>(m_name.rfind(L'\\'));
    if (separator == -1)
        separator = static_cast<int>(m_name.rfind(L'/'));
    return std::wstring(m_name, separator + 1, m_name.size());
}

std::wstring File::ext() const {
    const std::wstring name = getName();
    const auto dot = name.find(std::wstring(L"."));
    // The executable uses the first dot and includes it in the extension.
    if (dot == std::wstring::npos || dot == 0)
        return std::wstring(L"");
    return std::wstring(name, dot, std::wstring::npos);
}

int DeleteFileA(const char*);

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
