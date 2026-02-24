#pragma once

#include "java/io/OutputStream.h"

class BufferedOutputStream : public OutputStream {
public:
    BufferedOutputStream(OutputStream* outputStream, int bufferSize);

    ~BufferedOutputStream() override;
    void write(unsigned int) override;
    void write(arrayWithLength<unsigned char>) override;
    void write(arrayWithLength<unsigned char>, unsigned int, unsigned int) override;
    void close() override;
    void flush() override;

    OutputStream* m_outputStream;
    arrayWithLength<unsigned char> m_buffer;
    unsigned int m_size;
};
