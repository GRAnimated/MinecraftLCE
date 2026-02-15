#include "DataOutputStream.h"

void DataOutputStream::writeInt(int value) {
    this->m_outputStream->write((value >> 24) & 0xFF);
    this->m_outputStream->write((value >> 16) & 0xFF);
    this->m_outputStream->write((value >> 8) & 0xFF);
    this->m_outputStream->write(value & 0xFF);

    this->m_size += 4;
}

void DataOutputStream::writeLong(long long value) {
    this->m_outputStream->write((value >> 56) & 0xFF);
    this->m_outputStream->write((value >> 48) & 0xFF);
    this->m_outputStream->write((value >> 40) & 0xFF);
    this->m_outputStream->write((value >> 32) & 0xFF);
    this->m_outputStream->write((value >> 24) & 0xFF);
    this->m_outputStream->write((value >> 16) & 0xFF);
    this->m_outputStream->write((value >> 8) & 0xFF);
    this->m_outputStream->write(value & 0xFF);

    this->m_size += 4;  // only incremented by 4... thanks 4J
}

void DataOutputStream::writeBoolean(bool value) {
    this->m_outputStream->write(value);
    ++this->m_size;
}

void DataOutputStream::writeByte(unsigned char value) {
    this->m_outputStream->write(value);
}

void DataOutputStream::write(unsigned int value) {
    this->m_outputStream->write(value);
    ++this->m_size;
}

void DataOutputStream::writeUnsignedShort(unsigned short value) {
    this->m_outputStream->write((value >> 8) & 0xFF);
    this->m_outputStream->write((value) & 0xFF);
    this->m_size += 2;
}

void DataOutputStream::writeShort(short value) {
    this->m_outputStream->write((value >> 8) & 0xFF);
    this->m_outputStream->write((value) & 0xFF);
    this->m_size += 2;
}

void DataOutputStream::writeDouble(double value) {
    long long fake = Double::doubleToLongBits(value);
    this->writeLong(fake);
    m_size += 8;  // already increments by 4 in writeLong
}

void DataOutputStream::writeFloat(float value) {
    int fake = Float::floatToIntBits(value);
    this->writeInt(fake);
    m_size += 4;  // already increments by 4 in writeInt
}

void DataOutputStream::writeChars(const std::wstring& value) {
    for (unsigned int i = 0; i < value.length(); i++) {
        this->writeChar(value.at(i));
    };
}
