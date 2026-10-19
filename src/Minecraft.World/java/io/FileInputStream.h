#pragma once

#include "java/io/InputStream.h"
#include "nn/fs/fs_types.h"

class File;

class FileInputStream : public InputStream {
public:
    FileInputStream(const File& file);
    ~FileInputStream() override;

    int read() override;
    int read(arrayWithLength<unsigned char>) override;
    int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    long long skip(long long) override;
    unsigned int filesize();

    FileInputStream(const FileInputStream&) = delete;
    FileInputStream& operator=(const FileInputStream&) = delete;

private:
    nn::fs::FileHandle* m_file;
    bool m_eof;
};
