#include "com/mojang/nbt/FloatTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "net/minecraft/util/Mth.h"

FloatTag::FloatTag() : m_data(0.0f) {}

FloatTag::FloatTag(float data) : m_data(data) {}

void FloatTag::write(DataOutput* outputStream) {
    outputStream->writeFloat(m_data);
}

void FloatTag::load(DataInput* inputStream, int) {
    m_data = inputStream->readFloat();
}

std::wstring FloatTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%f", m_data);
    return buffer;
}

u8 FloatTag::getId() {
    return TAG_Float;
}

bool FloatTag::equals(Tag* other) {
    FloatTag* otherCasted = (FloatTag*)other;
    return Tag::equals(other) && m_data == otherCasted->m_data;
}

long FloatTag::getAsLong() {
    return m_data;
}

int FloatTag::getAsInt() {
    return Mth::floor(m_data);
}

short FloatTag::getAsShort() {
    return Mth::floor(m_data);
}

u8 FloatTag::getAsByte() {
    return Mth::floor(m_data);
}

double FloatTag::getAsDouble() {
    return m_data;
}

float FloatTag::getAsFloat() {
    return m_data;
}

Tag* FloatTag::copy() {
    return new FloatTag(m_data);
}
