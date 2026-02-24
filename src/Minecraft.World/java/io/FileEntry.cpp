#include "java/io/FileEntry.h"

#include "java/io/File.h"
#include <cstring>

FileEntry::FileEntry(wchar_t* a2, unsigned int a3, unsigned int a4) {
    m_offset = a3;
    m_length = a4;

    memset(this, 0, 0x80);
    memcpy(this, a2, 0x80);

    m_wFilename = char16towstring(a2);

    m_length2 = m_length;
    m_timestamp = 0;
    m_fieldAc = true;
}

bool FileEntry::newestFirst(FileEntry* a1, FileEntry* a2) {
    return a1->m_timestamp > a2->m_timestamp;
}
