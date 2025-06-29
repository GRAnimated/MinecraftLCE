#include "File.h"

File::File() {
    this->name = L"";
}

File::File(const std::wstring& name) {
    if (!name.empty()) {
        this->name = name;
    } else {
        this->name = std::wstring(L"");
    }
}

// NON_MATCHING | Score: 1075 (lower is better)
// Some std::wstring shenanigans
File::File(const File& rhs, const std::wstring& name) {
    this->name = rhs.getPath() + L"\\" + name;
}

File::~File() = default;

// NON_MATCHING | score: 805 (lower is better)
// Seems like I'm missing some kind of call
// Also, does it clear RHS' string?
File& File::operator=(const File& rhs) {
    this->name.clear();
    this->name = rhs.name;
    return *this;
}