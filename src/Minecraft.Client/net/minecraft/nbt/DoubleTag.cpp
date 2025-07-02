#include "net/minecraft/nbt/DoubleTag.h"

#include "net/minecraft/core/io/DataInput.h"
#include "net/minecraft/core/io/DataOutput.h"
#include "net/minecraft/util/Mth.h"
#include <cmath>

DoubleTag::DoubleTag() : mData(0.0f) {}

DoubleTag::DoubleTag(double data) : mData(data) {}

void DoubleTag::write(DataOutput* outputStream) {
    outputStream->writeDouble(mData);
}

void DoubleTag::load(DataInput* inputStream, int) {
    mData = inputStream->readDouble();
}

std::wstring DoubleTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%f", mData);
    return buffer;
}

u8 DoubleTag::getId() {
    return TAG_Double;
}

bool DoubleTag::equals(Tag* other) {
    DoubleTag* otherCasted = (DoubleTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long DoubleTag::getAsLong() {
    return floor(mData);
}

int DoubleTag::getAsInt() {
    return Mth::floor(mData);
}

short DoubleTag::getAsShort() {
    return Mth::floor(mData);
}

u8 DoubleTag::getAsByte() {
    return Mth::floor(mData);
}

double DoubleTag::getAsDouble() {
    return mData;
}

float DoubleTag::getAsFloat() {
    return mData;
}

Tag* DoubleTag::copy() {
    return new DoubleTag(mData);
}
