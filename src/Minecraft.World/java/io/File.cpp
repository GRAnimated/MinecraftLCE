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
