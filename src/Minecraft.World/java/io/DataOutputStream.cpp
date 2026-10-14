#include "DataOutputStream.h"
#include "net/minecraft/world/PlayerUID.h"
#include <cstring>
#include <memory>

DataOutputStream::DataOutputStream(OutputStream* output) : m_outputStream(output), m_size(0) {}
DataOutputStream::~DataOutputStream() {}

void DataOutputStream::flush() {
    m_outputStream->flush();
}
void DataOutputStream::close() {
    m_outputStream->close();
}
void DataOutputStream::write(arrayWithLength<unsigned char> bytes) {
    write(bytes, 0, bytes.m_length);
}
void DataOutputStream::writeBytes(arrayWithLength<unsigned char> bytes) {
    write(bytes, 0, bytes.m_length);
}
void DataOutputStream::write(arrayWithLength<unsigned char> bytes, unsigned int start, unsigned int length) {
    m_outputStream->write(bytes, start, length);
    m_size += length;
}
void DataOutputStream::deleteChildStream() {
    delete m_outputStream;
}

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

void DataOutputStream::writeChar(wchar_t value) {
    m_outputStream->write((value >> 8) & 0xff);
    m_outputStream->write(value & 0xff);
    m_size += 2;
}

void DataOutputStream::writeVarInt(int value) {
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    while (bits > 0x7f) {
        writeByte(static_cast<unsigned char>(bits | 0x80));
        bits >>= 7;
    }
    writeByte(static_cast<unsigned char>(bits));
}

void DataOutputStream::writeVarLong(JavaLong value) {
    std::uint64_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    while (bits > 0x7f) {
        writeByte(static_cast<unsigned char>(bits | 0x80));
        bits >>= 7;
    }
    writeByte(static_cast<unsigned char>(bits));
}

void DataOutputStream::writePlayerUID(PlayerUID uid) {
    static_assert(sizeof(PlayerUID) == 32, "PlayerUID wire format is 32 bytes");
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&uid);
    for (unsigned int i = 0; i < 32; ++i)
        writeByte(bytes[i]);
}

void DataOutputStream::writeUTF(const std::wstring& value) {
    unsigned int length = 0;
    for (unsigned int i = 0; i < value.length(); ++i) {
        unsigned int ch = value.at(i);
        length += ch >= 1 && ch <= 0x7f ? 1 : ch > 0x7ff ? 3 : 2;
    }
    arrayWithLength<unsigned char> bytes(length + 2, true);
    bytes[0] = (length >> 8) & 0xff;
    bytes[1] = length & 0xff;
    unsigned int offset = 2;
    for (unsigned int i = 0; i < value.length(); ++i) {
        unsigned int ch = value.at(i);
        if (ch >= 1 && ch <= 0x7f) {
            bytes[offset++] = ch;
        } else if (ch < 0x800) {
            bytes[offset++] = 0xc0 | ((ch >> 6) & 0x1f);
            bytes[offset++] = 0x80 | (ch & 0x3f);
        } else {
            bytes[offset++] = 0xe0 | ((ch >> 12) & 0x0f);
            bytes[offset++] = 0x80 | ((ch >> 6) & 0x3f);
            bytes[offset++] = 0x80 | (ch & 0x3f);
        }
    }
    write(bytes, 0, length + 2);
    delete[] bytes.m_data;
}
