#pragma once

#include "java/io/OutputStream.h"

class ConsoleSaveFile;
class FileEntry;

class ConsoleSaveFileOutputStream : public OutputStream {
public:
    void write(unsigned int) override;
    void write(arrayWithLength<unsigned char>) override;
    void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void flush() override;

    ConsoleSaveFile* mConsoleSaveFile;
    FileEntry* mFileEntry;
};
