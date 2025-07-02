#pragma once

#include "net/minecraft/core/io/OutputStream.h"

class ConsoleSaveFile;
class FileEntry;

class ConsoleSaveFileOutputStream : public OutputStream {
public:
    virtual void write(unsigned int) override;
    virtual void write(arrayWithLength<unsigned char>) override;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void flush() override;

    ConsoleSaveFile* mConsoleSaveFile;
    FileEntry* mFileEntry;
};
