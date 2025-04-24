#include "Minecraft.Nbt/LongTag.h"

#include "Minecraft.Core/io/DataInput.h"
#include "Minecraft.Core/io/DataOutput.h"

LongTag::LongTag() : mData(0) {}

LongTag::LongTag(long data) : mData(data) {}

void LongTag::write(DataOutput* outputStream) {
    outputStream->writeLong(mData);
}

void LongTag::load(DataInput* inputStream, int) {
    mData = inputStream->readLong();
}

std::wstring LongTag::toString() {
    static wchar_t buffer[32];
    swprintf(buffer, 32, L"%I64d", mData);
    return buffer;
}

u8 LongTag::getId() {
    return TAG_Long;
}

bool LongTag::equals(Tag* other) {
    LongTag* otherCasted = (LongTag*)other;
    return Tag::equals(other) && mData == otherCasted->mData;
}

long LongTag::getAsLong() {
    return mData;
}

int LongTag::getAsInt() {
    return mData;
}

short LongTag::getAsShort() {
    return mData;
}

u8 LongTag::getAsByte() {
    return mData;
}

double LongTag::getAsDouble() {
    return mData;
}

float LongTag::getAsFloat() {
    return mData;
}

Tag* LongTag::copy() {
    return new LongTag(mData);
}
