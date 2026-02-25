#include "com/mojang/nbt/ShortTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

ShortTag::ShortTag() {}

ShortTag::ShortTag(int data) : m_data(data) {}

void ShortTag::write(DataOutput* outputStream) {
    outputStream->writeShort(m_data);
}

void ShortTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readShort();
}

std::wstring ShortTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", m_data);
    return buffer;
}

u8 ShortTag::getId() {
    return TAG_Short;
}

bool ShortTag::equals(Tag* other) {
    ShortTag* otherCasted = (ShortTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long ShortTag::getAsLong() {
    return m_data;
}

int ShortTag::getAsInt() {
    return m_data;
}

short ShortTag::getAsShort() {
    return m_data;
}

u8 ShortTag::getAsByte() {
    return m_data;
}

double ShortTag::getAsDouble() {
    return m_data;
}

float ShortTag::getAsFloat() {
    return m_data;
}

Tag* ShortTag::copy() {
    return new ShortTag(m_data);
}
