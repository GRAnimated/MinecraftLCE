#pragma once

#include "Minecraft.Core/io/InputStream.h"

class ConsoleSaveFile;
class FileEntry;

class ConsoleSaveFileInputStream : public InputStream {
public:
    virtual unsigned int read() override;
    virtual void read(arrayWithLength<unsigned char>) override;
    virtual void read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void skip(long long) override;

    ConsoleSaveFile* mConsoleSaveFile;
    FileEntry* mFileEntry;
};
