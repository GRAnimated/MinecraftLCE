#include "com/mojang/nbt/FloatTag.h"

#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"
#include "net/minecraft/util/Mth.h"

FloatTag::FloatTag() : mData(0.0f) {}

FloatTag::FloatTag(float data) : mData(data) {}

void FloatTag::write(DataOutput* outputStream) {
    outputStream->writeFloat(mData);
}

void FloatTag::load(DataInput* inputStream, int) {
    mData = inputStream->readFloat();
}

std::wstring FloatTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%f", mData);
    return buffer;
}

u8 FloatTag::getId() {
    return TAG_Float;
}

bool FloatTag::equals(Tag* other) {
    FloatTag* otherCasted = (FloatTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long FloatTag::getAsLong() {
    return mData;
}

int FloatTag::getAsInt() {
    return Mth::floor(mData);
}

short FloatTag::getAsShort() {
    return Mth::floor(mData);
}

u8 FloatTag::getAsByte() {
    return Mth::floor(mData);
}

double FloatTag::getAsDouble() {
    return mData;
}

float FloatTag::getAsFloat() {
    return mData;
}

Tag* FloatTag::copy() {
    return new FloatTag(mData);
}
