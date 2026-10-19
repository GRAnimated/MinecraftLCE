#pragma once

#include "java/io/OutputStream.h"
#include "nn/fs/fs_types.h"

class File;

class FileOutputStream : public OutputStream {
public:
    FileOutputStream(const File&);

    ~FileOutputStream() override;
    void write(unsigned int) override;
    void write(arrayWithLength<unsigned char>) override;
    void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void flush() override;

    FileOutputStream(const FileOutputStream&) = delete;
    FileOutputStream& operator=(const FileOutputStream&) = delete;

    nn::fs::FileHandle* m_file;
};
