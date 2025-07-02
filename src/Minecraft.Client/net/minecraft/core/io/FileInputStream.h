#pragma once

#include "Minecraft.Core/io/InputStream.h"

class File;

class FileInputStream : public InputStream {
public:
    FileInputStream(const File& file);

    unsigned int read() override;
    void read(arrayWithLength<unsigned char>) override;
    void read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void skip(long long) override;

private:
    File* file;
    bool _10;
};
