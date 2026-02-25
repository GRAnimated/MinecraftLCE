#include "java/io/BufferedOutputStream.h"

#include "net/minecraft/world/ArrayWithLength.h"

BufferedOutputStream::BufferedOutputStream(OutputStream* outputStream, int bufferSize) {
    m_outputStream = outputStream;
    m_buffer = arrayWithLength<unsigned char>(bufferSize, true);
    m_size = 0;
}

BufferedOutputStream::~BufferedOutputStream() {
    delete m_buffer.m_data;
    m_buffer.m_data = nullptr;
}

void BufferedOutputStream::write(unsigned int byte) {
    m_buffer[m_size++] = byte;
    if (m_size == m_buffer.m_length) {
        flush();
    }
}

void BufferedOutputStream::write(arrayWithLength<unsigned char> array) {
    write(array, 0, array.m_length);
}

void BufferedOutputStream::write(arrayWithLength<unsigned char> array, unsigned int start,
                                 unsigned int length) {
    if (length >= m_buffer.m_length) {
        flush();
        m_outputStream->write(array, start, length);
        return;
    }
    for (unsigned int i = 0; i < length; ++i) {
        write(array[start + i]);
    }
}

void BufferedOutputStream::close() {
    flush();
    m_outputStream->close();
}

void BufferedOutputStream::flush() {
    m_outputStream->write(m_buffer, 0, m_size);
    m_size = 0;
}
