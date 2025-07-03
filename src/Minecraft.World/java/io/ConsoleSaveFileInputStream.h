#pragma once

#include "java/io/InputStream.h"

class ConsoleSaveFile;
class FileEntry;

class ConsoleSaveFileInputStream : public InputStream {
public:
    int read() override;
    int read(arrayWithLength<unsigned char>) override;
    int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    long long skip(long long) override;

    ConsoleSaveFile* mConsoleSaveFile;
    FileEntry* mFileEntry;
};
