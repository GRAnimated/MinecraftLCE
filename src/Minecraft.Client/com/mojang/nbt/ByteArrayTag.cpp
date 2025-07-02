#include "com/mojang/nbt/ByteArrayTag.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "net/minecraft/core/System.h"
#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"

ByteArrayTag::ByteArrayTag() {
    unknown = false;
}

ByteArrayTag::ByteArrayTag(arrayWithLength<u8> data, bool unk) {
    mData = data;
    unknown = unk;
}

ByteArrayTag::~ByteArrayTag() {
    if (unknown)
        delete mData.data;
}

void ByteArrayTag::write(DataOutput* outputStream) {
    outputStream->writeInt(mData.length);
    outputStream->write(mData);
}

void ByteArrayTag::load(DataInput* inputStream, int) {
    int len = inputStream->readInt();

    if (unknown) {
        delete[] mData.data;
    } else {
        unknown = true;
    }

    mData = arrayWithLength<u8>(len, true);
    inputStream->readFully(mData);
}

std::wstring ByteArrayTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"[%d bytes]", mData.length);
    return buffer;
}

u8 ByteArrayTag::getId() {
    return TAG_Byte_Array;
}

bool ByteArrayTag::equals(Tag* other) {
    if (!Tag::equals(other))
        return false;

    ByteArrayTag* otherCasted = (ByteArrayTag*)other;
    arrayWithLength<u8> data = this->mData;
    if (!data.data) {
        return otherCasted->mData.data == nullptr;
    }

    unsigned int len = mData.length;

    if (len == otherCasted->mData.length) {
        return memcmp(data.data, otherCasted->mData.data, len) == 0;
    }

    return false;
}

Tag* ByteArrayTag::copy() {
    arrayWithLength<u8> copy(mData.length, true);

    System::arraycopy(mData, 0, &copy, 0, mData.length);

    return new ByteArrayTag(copy, true);
}
