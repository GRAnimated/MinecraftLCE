#include "com/mojang/nbt/ByteTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

ByteTag::ByteTag() {}

ByteTag::ByteTag(u8 data) : m_data(data) {}

void ByteTag::write(DataOutput* outputStream) {
    outputStream->writeByte(m_data);
}

void ByteTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readChar();
}

std::wstring ByteTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", m_data);
    return buffer;
}

u8 ByteTag::getId() {
    return TAG_Byte;
}

bool ByteTag::equals(Tag* other) {
    ByteTag* otherCasted = (ByteTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long ByteTag::getAsLong() {
    return m_data;
}

int ByteTag::getAsInt() {
    return m_data;
}

short ByteTag::getAsShort() {
    return m_data;
}

u8 ByteTag::getAsByte() {
    return m_data;
}

double ByteTag::getAsDouble() {
    return m_data;
}

float ByteTag::getAsFloat() {
    return m_data;
}

Tag* ByteTag::copy() {
    return new ByteTag(m_data);
}
