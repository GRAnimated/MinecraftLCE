#include "java/io/ByteArrayOutputStream.h"

#include "NX/Platform.h"

ByteArrayOutputStream::ByteArrayOutputStream() {
    m_size = 0;
    m_buffer = arrayWithLength<unsigned char>(0x20, true);
}

ByteArrayOutputStream::ByteArrayOutputStream(unsigned int size) {
    m_size = 0;
    m_buffer = arrayWithLength<unsigned char>(size, true);
}

ByteArrayOutputStream::~ByteArrayOutputStream() {
    delete[] m_buffer.m_data;
}

void ByteArrayOutputStream::write(unsigned int byte) {
    if (m_size + 1 >= m_buffer.m_length)
        m_buffer.resize(m_buffer.m_length * 2);

    m_buffer[m_size] = byte;
    m_size++;
}

void ByteArrayOutputStream::write(arrayWithLength<unsigned char> array) {
    write(array, 0, array.m_length);
}

void ByteArrayOutputStream::write(arrayWithLength<unsigned char> array, unsigned int start,
                                  unsigned int length) {
    if (m_size + length >= m_buffer.m_length)
        m_buffer.resize(std::max(m_size + length + 1, m_buffer.m_length * 2));

    XMemCpy(&m_buffer[m_size], &array[start], length);

    m_size += length;
}

void ByteArrayOutputStream::close() {}

arrayWithLength<unsigned char> ByteArrayOutputStream::toByteArray() {
    return arrayWithLength<unsigned char>::createFromOther(m_buffer);
}
