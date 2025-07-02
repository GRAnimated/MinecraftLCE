#include "net/minecraft/core/io/FileEntry.h"

#include "net/minecraft/core/io/File.h"
#include <cstring>

FileEntry::FileEntry(wchar_t* a2, unsigned int a3, unsigned int a4) {
    mOffset = a3;
    mLength = a4;

    memset(this, 0, 0x80);
    memcpy(this, a2, 0x80);

    mWFilename = char16towstring(a2);

    mLength2 = mLength;
    mTimestamp = 0;
    field_ac = true;
}

bool FileEntry::newestFirst(FileEntry* a1, FileEntry* a2) {
    return a1->mTimestamp > a2->mTimestamp;
}
