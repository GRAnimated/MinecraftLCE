#pragma once

#include <string>

class FileEntry {
public:
    static bool newestFirst(FileEntry*, FileEntry*);

    FileEntry(wchar_t*, unsigned int, unsigned int);

    wchar_t mCharStream[0x20];
    unsigned int mOffset;
    unsigned int mLength;
    long mTimestamp;
    std::wstring qword_90;
    int mLength2;
    bool field_ac;
};
