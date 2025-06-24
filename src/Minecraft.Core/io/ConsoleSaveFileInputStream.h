#pragma once

#include "Minecraft.Core/io/InputStream.h"

class ConsoleSaveFile;
class FileEntry;

class ConsoleSaveFileInputStream : public InputStream {
public:
    virtual int read() override;
    virtual int read(arrayWithLength<unsigned char>) override;
    virtual int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual long long skip(long long) override;

    ConsoleSaveFile* mConsoleSaveFile;
    FileEntry* mFileEntry;
};
