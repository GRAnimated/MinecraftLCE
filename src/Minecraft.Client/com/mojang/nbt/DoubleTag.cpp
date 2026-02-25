#include "com/mojang/nbt/DoubleTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "net/minecraft/util/Mth.h"
#include <cmath>

DoubleTag::DoubleTag() : m_data(0.0f) {}

DoubleTag::DoubleTag(double data) : m_data(data) {}

void DoubleTag::write(DataOutput* outputStream) {
    outputStream->writeDouble(m_data);
}

void DoubleTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readDouble();
}

std::wstring DoubleTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%f", m_data);
    return buffer;
}

u8 DoubleTag::getId() {
    return TAG_Double;
}

bool DoubleTag::equals(Tag* other) {
    DoubleTag* otherCasted = (DoubleTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long DoubleTag::getAsLong() {
    return floor(m_data);
}

int DoubleTag::getAsInt() {
    return Mth::floor(m_data);
}

short DoubleTag::getAsShort() {
    return Mth::floor(m_data);
}

u8 DoubleTag::getAsByte() {
    return Mth::floor(m_data);
}

double DoubleTag::getAsDouble() {
    return m_data;
}

float DoubleTag::getAsFloat() {
    return m_data;
}

Tag* DoubleTag::copy() {
    return new DoubleTag(m_data);
}
