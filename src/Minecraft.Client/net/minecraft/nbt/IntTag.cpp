#include "net/minecraft/nbt/IntTag.h"

#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"

IntTag::IntTag() {}

IntTag::IntTag(int data) : mData(data) {}

void IntTag::write(DataOutput* outputStream) {
    outputStream->writeInt(mData);
}

void IntTag::load(DataInput* inputStream, int) {
    mData = inputStream->readInt();
}

std::wstring IntTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%d", mData);
    return buffer;
}

u8 IntTag::getId() {
    return TAG_Int;
}

bool IntTag::equals(Tag* other) {
    IntTag* otherCasted = (IntTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long IntTag::getAsLong() {
    return mData;
}

int IntTag::getAsInt() {
    return mData;
}

short IntTag::getAsShort() {
    return mData;
}

u8 IntTag::getAsByte() {
    return mData;
}

double IntTag::getAsDouble() {
    return mData;
}

float IntTag::getAsFloat() {
    return mData;
}

Tag* IntTag::copy() {
    return new IntTag(mData);
}
