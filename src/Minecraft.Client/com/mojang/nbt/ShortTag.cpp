#include "com/mojang/nbt/ShortTag.h"

#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"

ShortTag::ShortTag() {}

ShortTag::ShortTag(int data) : mData(data) {}

void ShortTag::write(DataOutput* outputStream) {
    outputStream->writeShort(mData);
}

void ShortTag::load(DataInput* inputStream, int) {
    mData = inputStream->readShort();
}

std::wstring ShortTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", mData);
    return buffer;
}

u8 ShortTag::getId() {
    return TAG_Short;
}

bool ShortTag::equals(Tag* other) {
    ShortTag* otherCasted = (ShortTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long ShortTag::getAsLong() {
    return mData;
}

int ShortTag::getAsInt() {
    return mData;
}

short ShortTag::getAsShort() {
    return mData;
}

u8 ShortTag::getAsByte() {
    return mData;
}

double ShortTag::getAsDouble() {
    return mData;
}

float ShortTag::getAsFloat() {
    return mData;
}

Tag* ShortTag::copy() {
    return new ShortTag(mData);
}
