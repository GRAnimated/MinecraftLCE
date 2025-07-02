#include "com/mojang/nbt/ByteTag.h"

#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"

ByteTag::ByteTag() {}

ByteTag::ByteTag(u8 data) : mData(data) {}

void ByteTag::write(DataOutput* outputStream) {
    outputStream->writeByte(mData);
}

void ByteTag::load(DataInput* inputStream, int) {
    mData = inputStream->readChar();
}

std::wstring ByteTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", mData);
    return buffer;
}

u8 ByteTag::getId() {
    return TAG_Byte;
}

bool ByteTag::equals(Tag* other) {
    ByteTag* otherCasted = (ByteTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long ByteTag::getAsLong() {
    return mData;
}

int ByteTag::getAsInt() {
    return mData;
}

short ByteTag::getAsShort() {
    return mData;
}

u8 ByteTag::getAsByte() {
    return mData;
}

double ByteTag::getAsDouble() {
    return mData;
}

float ByteTag::getAsFloat() {
    return mData;
}

Tag* ByteTag::copy() {
    return new ByteTag(mData);
}
