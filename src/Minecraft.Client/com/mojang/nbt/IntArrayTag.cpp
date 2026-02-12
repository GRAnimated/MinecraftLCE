#include "com/mojang/nbt/IntArrayTag.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include "net/minecraft/core/System.h"
#include <cstring>

IntArrayTag::IntArrayTag() {
    m_data = arrayWithLength<int>();  // it's already initialized in the header...
}

IntArrayTag::IntArrayTag(arrayWithLength<int> data) {
    m_data = data;
}

IntArrayTag::~IntArrayTag() {
    delete m_data.m_data;
}

void IntArrayTag::write(DataOutput* outputStream) {
    outputStream->writeInt(m_data.m_length);
    for (unsigned int i = 0; i < m_data.m_length; i++) {
        outputStream->writeInt(m_data[i]);
    }
}

void IntArrayTag::load(DataInput* inputStream, int) {
    int size = inputStream->readInt();

    // create a copy of the data
    int* data = m_data.m_data;
    if (data)
        delete data;

    m_data = arrayWithLength<int>(size, true);

    for (int i = 0; i < size; i++) {
        m_data[i] = inputStream->readInt();
    }
}

std::wstring IntArrayTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"[%d bytes]", m_data.m_length);
    return buffer;
}

u8 IntArrayTag::getId() {
    return TAG_Int_Array;
}

bool IntArrayTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    IntArrayTag* otherCasted = (IntArrayTag*)other;
    int* data = m_data.m_data;

    if (!data)
        return otherCasted->m_data.m_data == nullptr;

    unsigned int length = m_data.m_length;
    if (length == otherCasted->m_data.m_length)
        return memcmp(data, otherCasted->m_data.m_data, sizeof(int) * length) == 0;

    return false;
}

Tag* IntArrayTag::copy() {
    arrayWithLength<int> data = arrayWithLength<int>(m_data.m_length, true);  // copy
    System::arraycopy(m_data, 0, &data, 0, m_data.m_length);
    return new IntArrayTag(data);
}
