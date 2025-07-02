#pragma once

#include "Minecraft.Core/io/OutputStream.h"

class File;

class FileOutputStream : public OutputStream {
public:
    FileOutputStream(const File&);

    virtual ~FileOutputStream() override;
    virtual void write(unsigned int) override;
    virtual void write(arrayWithLength<unsigned char>) override;
    virtual void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    virtual void close() override;
    virtual void flush() override;

    void* field_8;
};
