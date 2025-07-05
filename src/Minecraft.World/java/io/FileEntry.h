#pragma once

#include <string>

class FileEntry {
public:
    static bool newestFirst(FileEntry*, FileEntry*);

    FileEntry(wchar_t*, unsigned int, unsigned int);

    wchar_t mFilename[0x20];
    unsigned int mOffset;
    unsigned int mLength;
    long mTimestamp;
    std::wstring mWFilename;
    int mLength2;
    bool field_ac;
};
