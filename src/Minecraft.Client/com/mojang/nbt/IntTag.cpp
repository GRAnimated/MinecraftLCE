#include "com/mojang/nbt/IntTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

IntTag::IntTag() {}

IntTag::IntTag(int data) : m_data(data) {}

void IntTag::write(DataOutput* outputStream) {
    outputStream->writeInt(m_data);
}

void IntTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readInt();
}

std::wstring IntTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", m_data);
    return buffer;
}

u8 IntTag::getId() {
    return TAG_Int;
}

bool IntTag::equals(Tag* other) {
    IntTag* otherCasted = (IntTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long IntTag::getAsLong() {
    return m_data;
}

int IntTag::getAsInt() {
    return m_data;
}

short IntTag::getAsShort() {
    return m_data;
}

u8 IntTag::getAsByte() {
    return m_data;
}

double IntTag::getAsDouble() {
    return m_data;
}

float IntTag::getAsFloat() {
    return m_data;
}

Tag* IntTag::copy() {
    return new IntTag(m_data);
}
