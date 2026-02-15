#pragma once

#include <string>

class FileEntry {
public:
    static bool newestFirst(FileEntry*, FileEntry*);

    FileEntry(wchar_t*, unsigned int, unsigned int);

    wchar_t m_filename[0x20];
    unsigned int m_offset;
    unsigned int m_length;
    long m_timestamp;
    std::wstring m_wFilename;
    int m_length2;
    bool m_fieldAc;
};
