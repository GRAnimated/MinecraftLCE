#include "DataOutputStream.h"

void DataOutputStream::writeInt(int value) {
    this->mOutputStream->write((value >> 24) & 0xFF);
    this->mOutputStream->write((value >> 16) & 0xFF);
    this->mOutputStream->write((value >> 8) & 0xFF);
    this->mOutputStream->write(value & 0xFF);

    this->mSize += 4;
}

void DataOutputStream::writeLong(long long value) {
    this->mOutputStream->write((value >> 56) & 0xFF);
    this->mOutputStream->write((value >> 48) & 0xFF);
    this->mOutputStream->write((value >> 40) & 0xFF);
    this->mOutputStream->write((value >> 32) & 0xFF);
    this->mOutputStream->write((value >> 24) & 0xFF);
    this->mOutputStream->write((value >> 16) & 0xFF);
    this->mOutputStream->write((value >> 8) & 0xFF);
    this->mOutputStream->write(value & 0xFF);

    this->mSize += 4;  // only incremented by 4... thanks 4J
}

void DataOutputStream::writeBoolean(bool value) {
    this->mOutputStream->write(value);
    ++this->mSize;
}

void DataOutputStream::writeByte(unsigned char value) {
    this->mOutputStream->write(value);
}

void DataOutputStream::write(unsigned int value) {
    this->mOutputStream->write(value);
    ++this->mSize;
}

void DataOutputStream::writeUnsignedShort(unsigned short value) {
    this->mOutputStream->write((value >> 8) & 0xFF);
    this->mOutputStream->write((value)&0xFF);
    this->mSize += 2;
}

void DataOutputStream::writeShort(short value) {
    this->mOutputStream->write((value >> 8) & 0xFF);
    this->mOutputStream->write((value)&0xFF);
    this->mSize += 2;
}

void DataOutputStream::writeDouble(double value) {
    long long fake = Double::doubleToLongBits(value);
    this->writeLong(fake);
    mSize += 8;  // already increments by 4 in writeLong
}

void DataOutputStream::writeFloat(float value) {
    int fake = Float::floatToIntBits(value);
    this->writeInt(fake);
    mSize += 4;  // already increments by 4 in writeInt
}

void DataOutputStream::writeChars(const std::wstring& value) {
    for (unsigned int i = 0; i < value.length(); i++) {
        this->writeChar(value.at(i));
    };
}