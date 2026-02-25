#include "java/io/ByteArrayInputStream.h"

#include "NX/Platform.h"

ByteArrayInputStream::ByteArrayInputStream(arrayWithLength<unsigned char> array, unsigned int start,
                                           unsigned int length) {
    m_length = std::min(start + length, array.m_length);
    m_currentPos = start;
    m_nextPos = start;
    m_buffer = array;
}

ByteArrayInputStream::ByteArrayInputStream(arrayWithLength<unsigned char> array) {
    m_length = array.m_length;
    m_currentPos = 0;
    m_nextPos = 0;
    m_buffer = array;
}

ByteArrayInputStream::~ByteArrayInputStream() {
    delete[] m_buffer.m_data;
}

int ByteArrayInputStream::read() {
    if (m_nextPos < m_length)
        return m_buffer[m_nextPos++];
    return -1;
}

int ByteArrayInputStream::read(arrayWithLength<unsigned char> array) {
    return read(array, 0, array.m_length);
}

int ByteArrayInputStream::read(arrayWithLength<unsigned char> array, unsigned int start,
                               unsigned int length) {
    if (m_nextPos == m_length)
        return -1;

    int amount = std::min(length, m_length - m_nextPos);
    XMemCpy(&array[start], &m_buffer[m_nextPos], amount);
    m_nextPos += amount;

    return amount;
}

void ByteArrayInputStream::close() {}

long long ByteArrayInputStream::skip(long long amount) {
    int newPos = m_nextPos + amount;

    if (newPos > m_length)
        newPos = m_length;

    int difference = newPos - m_nextPos;
    m_nextPos = newPos;

    return difference;
}
