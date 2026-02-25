#include "com/mojang/nbt/ByteArrayTag.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "net/minecraft/core/System.h"

ByteArrayTag::ByteArrayTag() {
    m_unknown = false;
}

ByteArrayTag::ByteArrayTag(arrayWithLength<u8> data, bool unk) {
    m_data = data;
    m_unknown = unk;
}

ByteArrayTag::~ByteArrayTag() {
    if (m_unknown)
        delete m_data.m_data;
}

void ByteArrayTag::write(DataOutput* outputStream) {
    outputStream->writeInt(m_data.m_length);
    outputStream->write(m_data);
}

void ByteArrayTag::load(DataInput* inputStream, int) {
    int len = inputStream->readInt();

    if (m_unknown) {
        delete[] m_data.m_data;
    } else {
        m_unknown = true;
    }

    m_data = arrayWithLength<u8>(len, true);
    inputStream->readFully(m_data);
}

std::wstring ByteArrayTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"[%d bytes]", m_data.m_length);
    return buffer;
}

u8 ByteArrayTag::getId() {
    return TAG_Byte_Array;
}

bool ByteArrayTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    ByteArrayTag* otherCasted = (ByteArrayTag*)other;
    arrayWithLength<u8> data = this->m_data;
    if (!data.m_data) {
        return otherCasted->m_data.m_data == nullptr;
    }

    unsigned int len = m_data.m_length;

    if (len == otherCasted->m_data.m_length) {
        return memcmp(data.m_data, otherCasted->m_data.m_data, len) == 0;
    }

    return false;
}

Tag* ByteArrayTag::copy() {
    arrayWithLength<u8> copy(m_data.m_length, true);

    System::arraycopy(m_data, 0, &copy, 0, m_data.m_length);

    return new ByteArrayTag(copy, true);
}
