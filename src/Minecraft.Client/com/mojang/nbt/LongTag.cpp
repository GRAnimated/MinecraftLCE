#include "com/mojang/nbt/LongTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

LongTag::LongTag() : m_data(0) {}

LongTag::LongTag(long data) : m_data(data) {}

void LongTag::write(DataOutput* outputStream) {
    outputStream->writeLong(m_data);
}

void LongTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readLong();
}

std::wstring LongTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%I64d", m_data);
    return buffer;
}

u8 LongTag::getId() {
    return TAG_Long;
}

bool LongTag::equals(Tag* other) {
    LongTag* otherCasted = (LongTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long LongTag::getAsLong() {
    return m_data;
}

int LongTag::getAsInt() {
    return m_data;
}

short LongTag::getAsShort() {
    return m_data;
}

u8 LongTag::getAsByte() {
    return m_data;
}

double LongTag::getAsDouble() {
    return m_data;
}

float LongTag::getAsFloat() {
    return m_data;
}

Tag* LongTag::copy() {
    return new LongTag(m_data);
}
