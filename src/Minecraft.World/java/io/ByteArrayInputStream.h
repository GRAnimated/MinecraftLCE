#pragma once

#include "java/io/InputStream.h"

class ByteArrayInputStream : public InputStream {
public:
    ByteArrayInputStream(arrayWithLength<unsigned char> array, unsigned int start, unsigned int length);
    ByteArrayInputStream(arrayWithLength<unsigned char> array);
    ByteArrayInputStream();

    ~ByteArrayInputStream() override;
    int read() override;
    int read(arrayWithLength<unsigned char>) override;
    int read(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    long long skip(long long) override;

    arrayWithLength<unsigned char> m_buffer;
    unsigned int m_length;
    unsigned int m_currentPos;
    unsigned int m_nextPos;
};
